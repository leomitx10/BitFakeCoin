#pragma once
#include "../wallet/Wallet.h"
#include <string>
#include <memory>
#include <nlohmann/json.hpp>
#include <chrono>

class User {
private:
    std::string username;
    std::string passwordHash;
    std::shared_ptr<Wallet> wallet;
    std::string email;
    std::string fullName;
    std::chrono::system_clock::time_point createdAt;

public:
    User(const std::string& username, 
         const std::string& password, 
         std::shared_ptr<Wallet> wallet,
         const std::string& email = "",
         const std::string& fullName = "")
        : username(username)
        , passwordHash(password)
        , wallet(wallet)
        , email(email)
        , fullName(fullName)
        , createdAt(std::chrono::system_clock::now()) {}

    const std::string& getUsername() const { return username; }
    const std::string& getPasswordHash() const { return passwordHash; }
    const std::string& getEmail() const { return email; }
    const std::string& getFullName() const { return fullName; }
    std::shared_ptr<Wallet> getWallet() const { return wallet; }

    nlohmann::json toJson() const {
        nlohmann::json j;
        j["username"] = username;
        j["email"] = email;
        j["fullName"] = fullName;
        j["walletAddress"] = wallet->getAddress();
        j["balance"] = wallet->getBalance();
        j["createdAt"] = std::chrono::duration_cast<std::chrono::milliseconds>(
            createdAt.time_since_epoch()
        ).count();
        return j;
    }
};
