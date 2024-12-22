#include "Blockchain.h"

Blockchain::Blockchain() : difficulty(4) {
    // Create genesis block
    chain.emplace_back(Block(0, "Genesis Block", "0"));
}

Block Blockchain::getLatestBlock() const {
    return chain.back();
}

void Blockchain::addBlock(const std::string& data) {
    Block previousBlock = getLatestBlock();
    Block newBlock(previousBlock.getIndex() + 1, data, previousBlock.getHash());
    
    newBlock.mineBlock(difficulty);
    chain.push_back(newBlock);
}

bool Blockchain::isChainValid() const {
    for (size_t i = 1; i < chain.size(); i++) {
        const Block& currentBlock = chain[i];
        const Block& previousBlock = chain[i - 1];
        
        if (currentBlock.getHash() != currentBlock.calculateHash()) {
            return false;
        }
        
        if (currentBlock.getPreviousHash() != previousBlock.getHash()) {
            return false;
        }
    }
    return true;
}
