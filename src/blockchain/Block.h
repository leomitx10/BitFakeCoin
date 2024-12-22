#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iostream>
#include <memory>
#include "../utils/SHA256.h"
#include "Transaction.h"

class Block {
private:
    int index;
    int64_t nonce;
    std::vector<std::shared_ptr<Transaction>> transactions;
    std::string hash;
    std::string previousHash;
    time_t timestamp;

public:
    Block(int idx, const std::vector<std::shared_ptr<Transaction>>& txs, const std::string& prevHash);
    
    std::string calculateHash() const;
    void mineBlock(int difficulty);
    
    // Getters
    std::string getHash() const { return hash; }
    std::string getPreviousHash() const { return previousHash; }
    const std::vector<std::shared_ptr<Transaction>>& getTransactions() const { return transactions; }
    int getIndex() const { return index; }
};
