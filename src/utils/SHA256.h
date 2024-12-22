#pragma once
#include <string>
#include <openssl/evp.h>
#include <sstream>
#include <iomanip>

class SHA256 {
public:
    static std::string hash(const std::string& input) {
        unsigned char hash[EVP_MAX_MD_SIZE];
        unsigned int length;

        EVP_MD_CTX* context = EVP_MD_CTX_new();
        if(context != nullptr) {
            if(EVP_DigestInit_ex(context, EVP_sha256(), nullptr)) {
                if(EVP_DigestUpdate(context, input.c_str(), input.length())) {
                    if(EVP_DigestFinal_ex(context, hash, &length)) {
                        std::stringstream ss;
                        for(unsigned int i = 0; i < length; i++) {
                            ss << std::hex << std::setw(2) << std::setfill('0') 
                               << static_cast<int>(hash[i]);
                        }
                        EVP_MD_CTX_free(context);
                        return ss.str();
                    }
                }
            }
            EVP_MD_CTX_free(context);
        }
        return "";
    }
};
