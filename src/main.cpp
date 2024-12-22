#include "api/CryptoAPI.h"
#include <iostream>

int main() {
    std::cout << "Starting Cryptocurrency API Server..." << std::endl;
    
    CryptoAPI api;
    api.start(3000);
    
    return 0;
}
