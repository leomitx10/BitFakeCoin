#pragma once
#include <string>
#include <vector>
#include <memory>
#include <random>
#include <nlohmann/json.hpp>
#include "../blockchain/Transaction.h"
#include "../blockchain/Blockchain.h"
#include <openssl/evp.h>
#include <openssl/pem.h>

class Wallet {
private:
    std::string address;
    std::string ownerUsername;  // Nome do usuário dono da carteira
    EVP_PKEY* keypair;
    std::shared_ptr<Blockchain> blockchain;
    std::vector<std::shared_ptr<Transaction>> transactionHistory;  // Histórico de transações

    static std::string generateAddress() {
        const std::string chars = "0123456789abcdef";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, chars.size() - 1);

        std::string address = "0x";
        for (int i = 0; i < 40; ++i) {
            address += chars[dis(gen)];
        }
        return address;
    }

    // Atualiza o histórico de transações da carteira
    void updateTransactionHistory() {
        transactionHistory.clear();
        
        // Percorre todos os blocos procurando transações relacionadas a esta carteira
        for (const auto& block : blockchain->getChain()) {
            for (const auto& tx : block.getTransactions()) {
                if (tx->getFromAddress() == address || tx->getToAddress() == address) {
                    transactionHistory.push_back(tx);
                }
            }
        }
    }

public:
    Wallet(std::shared_ptr<Blockchain> bc, const std::string& username) 
        : address(generateAddress()), ownerUsername(username), blockchain(bc) {}
    
    virtual ~Wallet() = default;

    const std::string& getAddress() const { return address; }
    const std::string& getOwnerUsername() const { return ownerUsername; }
    
    double getBalance() const {
        return blockchain->getBalance(address);
    }

    bool sendTransaction(const std::string& recipient, double amount) {
        if (amount <= 0 || amount > getBalance()) {
            return false;
        }

        auto tx = std::make_shared<Transaction>(
            Transaction::Type::SEND,
            address,
            recipient,
            amount
        );
        
        if (blockchain->addTransaction(tx)) {
            transactionHistory.push_back(tx);
            return true;
        }
        return false;
    }

    std::vector<nlohmann::json> getTransactionHistory() {
        // Atualiza o histórico antes de retornar
        updateTransactionHistory();
        
        std::vector<nlohmann::json> history;
        for (const auto& tx : transactionHistory) {
            nlohmann::json txJson = tx->toJson();
            
            // Adiciona informação se a transação é de entrada ou saída
            if (tx->getFromAddress() == address) {
                txJson["type"] = "sent";
                txJson["impact"] = -tx->getAmount();
            } else {
                txJson["type"] = "received";
                txJson["impact"] = tx->getAmount();
            }
            
            history.push_back(txJson);
        }
        
        return history;
    }

    nlohmann::json toJson() const {
        nlohmann::json j;
        j["address"] = address;
        j["ownerUsername"] = ownerUsername;
        j["balance"] = getBalance();
        return j;
    }

    void generateKeyPair();
};
