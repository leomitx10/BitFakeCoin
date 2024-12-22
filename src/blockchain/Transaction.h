#pragma once
#include <string>
#include <chrono>
#include <nlohmann/json.hpp>

class Transaction {
public:
    enum class Type {
        SEND,
        MINING_REWARD
    };

private:
    Type type;
    std::string fromAddress;
    std::string toAddress;
    double amount;
    std::chrono::system_clock::time_point timestamp;

public:
    Transaction(Type type, const std::string& from, const std::string& to, double amount)
        : type(type)
        , fromAddress(from)
        , toAddress(to)
        , amount(amount)
        , timestamp(std::chrono::system_clock::now()) {}

    Type getType() const { return type; }
    const std::string& getFromAddress() const { return fromAddress; }
    const std::string& getToAddress() const { return toAddress; }
    double getAmount() const { return amount; }
    
    std::string getTypeString() const {
        switch (type) {
            case Type::SEND:
                return "transfer";
            case Type::MINING_REWARD:
                return "mining_reward";
            default:
                return "unknown";
        }
    }

    nlohmann::json toJson() const {
        nlohmann::json j;
        j["type"] = getTypeString();
        j["from"] = fromAddress;
        j["to"] = toAddress;
        j["amount"] = amount;
        j["timestamp"] = std::chrono::duration_cast<std::chrono::milliseconds>(
            timestamp.time_since_epoch()
        ).count();
        return j;
    }
};
