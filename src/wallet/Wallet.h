#pragma once
#include <string>
#include <vector>
#include <memory>
#include <random>
#include <nlohmann/json.hpp>
#include "../blockchain/Transaction.h"
#include <openssl/evp.h>
#include <openssl/pem.h>

class Transaction;

class Wallet {
private:
    std::string address;
    double balance;
    EVP_PKEY* keypair;
    std::vector<std::shared_ptr<Transaction>> transactions;

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

public:
    Wallet() : address(generateAddress()), balance(0.0) {}
    virtual ~Wallet() = default;

    const std::string& getAddress() const { return address; }
    double getBalance() const { return balance; }

    bool sendTransaction(const std::string& recipient, double amount) {
        if (amount <= 0 || amount > balance) {
            return false;
        }

        balance -= amount;
        auto tx = std::make_shared<Transaction>(
            Transaction::Type::SEND,
            address,
            recipient,
            amount
        );
        transactions.push_back(tx);
        return true;
    }

    void receiveTransaction(double amount, const std::string& from = "system") {
        if (amount <= 0) return;

        balance += amount;
        auto tx = std::make_shared<Transaction>(
            from == "system" ? Transaction::Type::MINING_REWARD : Transaction::Type::RECEIVE,
            from,
            address,
            amount
        );
        transactions.push_back(tx);
    }

    std::vector<nlohmann::json> getTransactionHistory(size_t limit = 50) const {
        std::vector<nlohmann::json> history;
        
        size_t count = 0;
        for (auto it = transactions.rbegin(); it != transactions.rend() && count < limit; ++it, ++count) {
            history.push_back((*it)->toJson());
        }
        
        return history;
    }

    void generateKeyPair();
};
