#include "Block.h"
#include <nlohmann/json.hpp>

Block::Block(int idx, const std::vector<std::shared_ptr<Transaction>>& txs, const std::string& prevHash) 
    : index(idx), transactions(txs), previousHash(prevHash), nonce(0) {
    timestamp = time(nullptr);
    hash = calculateHash();
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index << timestamp << previousHash << nonce;
    
    // Adicionar hash das transações
    for (const auto& tx : transactions) {
        ss << tx->toJson().dump();
    }
    
    return SHA256::hash(ss.str());
}

void Block::mineBlock(int difficulty) {
    std::string target(difficulty, '0');
    
    while (hash.substr(0, difficulty) != target) {
        nonce++;
        hash = calculateHash();
    }
    
    std::cout << "Block mined: " << hash << std::endl;
}
