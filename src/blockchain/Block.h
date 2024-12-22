#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iostream>
#include "../utils/SHA256.h"

class Block {
private:
    int index;
    int64_t nonce;
    std::string data;
    std::string hash;
    std::string previousHash;
    time_t timestamp;

public:
    Block(int idx, const std::string& data, const std::string& prevHash);
    
    std::string calculateHash() const;
    void mineBlock(int difficulty);
    
    // Getters
    std::string getHash() const { return hash; }
    std::string getPreviousHash() const { return previousHash; }
    std::string getData() const { return data; }
    int getIndex() const { return index; }
};
