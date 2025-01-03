#pragma once
#include <crow.h>
#include <nlohmann/json.hpp>
#include "../blockchain/Blockchain.h"
#include "../wallet/Wallet.h"
#include "User.h"
#include <map>
#include <memory>
#include <jwt-cpp/jwt.h>
#include <filesystem>

class CryptoAPI {
private:
    crow::SimpleApp app;
    std::shared_ptr<Blockchain> blockchain;
    std::map<std::string, std::shared_ptr<User>> users;
    std::map<std::string, std::shared_ptr<Wallet>> wallets;
    const std::string JWT_SECRET = "your-secret-key";
    std::string publicDir;

    // Converter nlohmann::json para crow::json::wvalue
    crow::json::wvalue nlohmannToCrow(const nlohmann::json& j) {
        if (j.is_object()) {
            crow::json::wvalue w;
            for (auto& [key, value] : j.items()) {
                if (value.is_string()) w[key] = value.get<std::string>();
                else if (value.is_number_integer()) w[key] = value.get<int64_t>();
                else if (value.is_number_float()) w[key] = value.get<double>();
                else if (value.is_boolean()) w[key] = value.get<bool>();
                else if (value.is_array()) w[key] = nlohmannToCrow(value);
                else if (value.is_object()) w[key] = nlohmannToCrow(value);
                else if (value.is_null()) w[key] = nullptr;
            }
            return w;
        }
        else if (j.is_array()) {
            std::vector<crow::json::wvalue> arr;
            for (const auto& elem : j) {
                arr.push_back(nlohmannToCrow(elem));
            }
            return crow::json::wvalue(arr);
        }
        return crow::json::wvalue(nullptr);
    }

public:
    CryptoAPI() : blockchain(std::make_shared<Blockchain>()) {
        // Encontrar o diretório public
        publicDir = std::filesystem::current_path().parent_path() / "public";
        setupRoutes();
    }

    void start(uint16_t port = 3000) {
        // Servir arquivos estáticos
        CROW_ROUTE(app, "/")
        ([this](const crow::request& req) {
            return serveFile("/index.html");
        });

        CROW_ROUTE(app, "/<path>")
        ([this](const crow::request& req, const std::string& path) {
            return serveFile("/" + path);
        });

        app.port(port).multithreaded().run();
    }

private:
    crow::response serveFile(const std::string& path) {
        std::string fullPath = publicDir + path;
        
        // Se o arquivo não existir, retornar 404
        if (!std::filesystem::exists(fullPath)) {
            return crow::response(404);
        }

        // Ler o arquivo
        std::ifstream file(fullPath, std::ios::binary);
        if (!file) {
            return crow::response(500);
        }

        std::string content((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());

        crow::response res;
        res.code = 200;

        // Definir o Content-Type baseado na extensão do arquivo
        std::string ext = std::filesystem::path(path).extension();
        if (ext == ".html") res.add_header("Content-Type", "text/html");
        else if (ext == ".css") res.add_header("Content-Type", "text/css");
        else if (ext == ".js") res.add_header("Content-Type", "application/javascript");
        else if (ext == ".json") res.add_header("Content-Type", "application/json");
        else res.add_header("Content-Type", "text/plain");

        res.body = content;
        return res;
    }

    std::string generateToken(const std::string& username) {
        return jwt::create()
            .set_issuer("crypto-project")
            .set_type("JWS")
            .set_payload_claim("username", jwt::claim(username))
            .set_issued_at(std::chrono::system_clock::now())
            .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours{24})
            .sign(jwt::algorithm::hs256{JWT_SECRET});
    }

    bool verifyToken(const std::string& token, std::string& username) {
        try {
            auto decoded = jwt::decode(token);
            auto verifier = jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256{JWT_SECRET})
                .with_issuer("crypto-project");
            verifier.verify(decoded);
            username = decoded.get_payload_claim("username").as_string();
            return true;
        } catch (const std::exception&) {
            return false;
        }
    }

    void setupRoutes() {
        // Autenticação
        CROW_ROUTE(app, "/api/auth/register")
            .methods("POST"_method)
        ([this](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body) return crow::response(400, "Invalid JSON");

            if (!body.has("username") || !body.has("password")) {
                return crow::response(400, "Username and password are required");
            }

            std::string username = body["username"].s();
            std::string password = body["password"].s();
            std::string email;
            std::string fullName;

            // Verificar campos opcionais
            if (body.has("email")) {
                email = body["email"].s();
            }
            if (body.has("fullName")) {
                fullName = body["fullName"].s();
            }

            if (users.find(username) != users.end()) {
                return crow::response(409, "Username already exists");
            }

            auto wallet = std::make_shared<Wallet>(blockchain, username);
            wallets[wallet->getAddress()] = wallet;
            auto user = std::make_shared<User>(username, password, wallet, email, fullName);
            users[username] = user;

            // Gerar token JWT
            std::string token = generateToken(username);

            crow::json::wvalue response;
            response["message"] = "User created successfully";
            response["token"] = token;
            response["user"] = {
                {"username", username},
                {"walletAddress", wallet->getAddress()},
                {"balance", wallet->getBalance()}
            };
            return crow::response(201, response);
        });

        CROW_ROUTE(app, "/api/auth/login")
            .methods("POST"_method)
        ([this](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body) return crow::response(400, "Invalid JSON");

            if (!body.has("username") || !body.has("password")) {
                return crow::response(400, "Username and password are required");
            }

            std::string username = body["username"].s();
            std::string password = body["password"].s();

            auto it = users.find(username);
            if (it == users.end() || it->second->getPasswordHash() != password) {
                return crow::response(401, "Invalid username or password");
            }

            // Gerar token JWT
            std::string token = generateToken(username);

            auto user = it->second;
            auto wallet = user->getWallet();

            crow::json::wvalue response;
            response["token"] = token;
            response["user"] = {
                {"username", username},
                {"walletAddress", wallet->getAddress()},
                {"balance", wallet->getBalance()}
            };
            return crow::response(200, response);
        });

        // Informações da carteira
        CROW_ROUTE(app, "/api/wallet/info")
        ([this](const crow::request& req) {
            std::string username;
            std::string token = req.get_header_value("Authorization").substr(7); // Remove "Bearer "
            
            if (!verifyToken(token, username)) {
                return crow::response(401, "Invalid token");
            }

            auto user = users[username];
            auto wallet = user->getWallet();

            crow::json::wvalue response;
            response["address"] = wallet->getAddress();
            response["balance"] = wallet->getBalance();
            return crow::response{response};
        });

        // Enviar transação
        CROW_ROUTE(app, "/api/transactions/send")
            .methods("POST"_method)
        ([this](const crow::request& req) {
            std::string username;
            std::string token = req.get_header_value("Authorization").substr(7);
            
            if (!verifyToken(token, username)) {
                return crow::response(401, "Invalid token");
            }

            auto body = crow::json::load(req.body);
            if (!body) return crow::response(400, "Invalid JSON");

            if (!body.has("to") || !body.has("amount")) {
                return crow::response(400, "Recipient address and amount are required");
            }

            std::string recipientAddress = body["to"].s();
            double amount = body["amount"].d();

            auto user = users[username];
            auto wallet = user->getWallet();

            if (amount <= 0) {
                return crow::response(400, "Amount must be greater than 0");
            }

            if (wallet->getBalance() < amount) {
                return crow::response(400, "Insufficient balance");
            }

            // Criar e adicionar a transação
            auto transaction = std::make_shared<Transaction>(
                Transaction::Type::SEND,
                wallet->getAddress(),
                recipientAddress,
                amount
            );

            if (!blockchain->addTransaction(transaction)) {
                return crow::response(400, "Transaction failed");
            }

            crow::json::wvalue response;
            response["message"] = "Transaction added to pending transactions";
            response["transaction"] = {
                {"from", wallet->getAddress()},
                {"to", recipientAddress},
                {"amount", amount},
                {"status", "pending"}
            };
            return crow::response(201, response);
        });

        // Histórico de transações
        CROW_ROUTE(app, "/api/transactions/history")
        ([this](const crow::request& req) {
            std::string username;
            std::string token = req.get_header_value("Authorization").substr(7);
            
            if (!verifyToken(token, username)) {
                return crow::response(401, "Invalid token");
            }

            auto user = users[username];
            auto wallet = user->getWallet();
            auto transactions = blockchain->getTransactionHistory(wallet->getAddress());

            crow::json::wvalue response;
            std::vector<crow::json::wvalue> txArray;

            for (const auto& tx : transactions) {
                auto txJson = tx->toJson();
                
                // Adicionar informações específicas para o usuário
                bool isSender = (tx->getFromAddress() == wallet->getAddress());
                
                crow::json::wvalue txResponse;
                txResponse["type"] = txJson["type"].get<std::string>();
                txResponse["direction"] = isSender ? "sent" : "received";
                txResponse["from"] = txJson["from"].get<std::string>();
                txResponse["to"] = txJson["to"].get<std::string>();
                txResponse["amount"] = txJson["amount"].get<double>();
                txResponse["timestamp"] = txJson["timestamp"].get<int64_t>();
                txResponse["impact"] = isSender ? -txJson["amount"].get<double>() : txJson["amount"].get<double>();
                
                // Adicionar descrição amigável
                std::string description;
                if (tx->getType() == Transaction::Type::MINING_REWARD) {
                    description = "Mining Reward";
                } else if (isSender) {
                    description = "Sent to " + tx->getToAddress().substr(0, 8) + "...";
                } else {
                    description = "Received from " + tx->getFromAddress().substr(0, 8) + "...";
                }
                txResponse["description"] = description;
                
                txArray.push_back(std::move(txResponse));
            }

            response["transactions"] = std::move(txArray);
            response["balance"] = wallet->getBalance();
            response["address"] = wallet->getAddress();
            return crow::response{response};
        });

        // Mineração
        CROW_ROUTE(app, "/api/mining/start")
            .methods("POST"_method)
        ([this](const crow::request& req) {
            std::string username;
            std::string token = req.get_header_value("Authorization").substr(7);
            
            if (!verifyToken(token, username)) {
                return crow::response(401, "Invalid token");
            }

            auto user = users[username];
            auto wallet = user->getWallet();
            
            // Minerar transações pendentes e receber recompensa
            blockchain->minePendingTransactions(wallet->getAddress());

            crow::json::wvalue response;
            response["success"] = true;
            response["reward"] = 50.0; // Valor definido no blockchain
            return crow::response{response};
        });
    }
};
