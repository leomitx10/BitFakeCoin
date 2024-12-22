#pragma once
#include <vector>
#include <memory>
#include "Block.h"
#include "Transaction.h"

class Blockchain {
private:
    std::vector<Block> chain;
    std::vector<std::shared_ptr<Transaction>> pendingTransactions;
    int difficulty;
    double miningReward;
    
    Block getLatestBlock() const;

public:
    Blockchain();
    
    bool addTransaction(std::shared_ptr<Transaction> transaction);
    void minePendingTransactions(const std::string& minerAddress);
    double getBalance(const std::string& address) const;
    std::vector<std::shared_ptr<Transaction>> getTransactionHistory(const std::string& address) const;
    const std::vector<Block>& getChain() const { return chain; }
    int getDifficulty() const { return difficulty; }
    bool isChainValid() const;
};
