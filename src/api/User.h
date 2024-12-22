#pragma once
#include "../wallet/Wallet.h"
#include <string>
#include <memory>

class User {
private:
    std::string username;
    std::string passwordHash;
    std::shared_ptr<Wallet> wallet;

public:
    User(const std::string& username, const std::string& password, std::shared_ptr<Wallet> wallet)
        : username(username), passwordHash(password), wallet(wallet) {}

    const std::string& getUsername() const { return username; }
    const std::string& getPasswordHash() const { return passwordHash; }
    std::shared_ptr<Wallet> getWallet() const { return wallet; }
};
