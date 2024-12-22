#pragma once
#include <string>
#include <chrono>
#include <nlohmann/json.hpp>

class Transaction {
public:
    enum class Type {
        SEND,
        RECEIVE,
        MINING_REWARD
    };

    Transaction(
        Type type,
        const std::string& fromAddress,
        const std::string& toAddress,
        double amount,
        std::chrono::system_clock::time_point timestamp = std::chrono::system_clock::now()
    ) : type(type), fromAddress(fromAddress), toAddress(toAddress), amount(amount), timestamp(timestamp) {}

    Type getType() const { return type; }
    const std::string& getFromAddress() const { return fromAddress; }
    const std::string& getToAddress() const { return toAddress; }
    double getAmount() const { return amount; }
    std::chrono::system_clock::time_point getTimestamp() const { return timestamp; }

    // Converter para JSON
    nlohmann::json toJson() const {
        nlohmann::json json;
        json["type"] = typeToString(type);
        json["from"] = fromAddress;
        json["to"] = toAddress;
        json["amount"] = amount;
        json["timestamp"] = std::chrono::duration_cast<std::chrono::milliseconds>(
            timestamp.time_since_epoch()
        ).count();
        return json;
    }

private:
    Type type;
    std::string fromAddress;
    std::string toAddress;
    double amount;
    std::chrono::system_clock::time_point timestamp;

    static std::string typeToString(Type type) {
        switch (type) {
            case Type::SEND: return "send";
            case Type::RECEIVE: return "receive";
            case Type::MINING_REWARD: return "mining_reward";
            default: return "unknown";
        }
    }
};
