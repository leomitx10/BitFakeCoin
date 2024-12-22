#pragma once
#include <vector>
#include "Block.h"

class Blockchain {
private:
    std::vector<Block> chain;
    int difficulty;
    
    Block getLatestBlock() const;

public:
    Blockchain();
    
    void addBlock(const std::string& data);
    const std::vector<Block>& getChain() const { return chain; }
    int getDifficulty() const { return difficulty; }
    bool isChainValid() const;
};
