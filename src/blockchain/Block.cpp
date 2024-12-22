#include "Block.h"

Block::Block(int idx, const std::string& data, const std::string& prevHash) 
    : index(idx), data(data), previousHash(prevHash), nonce(0) {
    timestamp = time(nullptr);
    hash = calculateHash();
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index << timestamp << data << previousHash << nonce;
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
