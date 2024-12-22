#include "Blockchain.h"

Blockchain::Blockchain() : difficulty(4), miningReward(50.0) {
    // Criar o bloco gênesis
    std::vector<std::shared_ptr<Transaction>> genesisTransactions;
    chain.emplace_back(0, genesisTransactions, "0");
}

Block Blockchain::getLatestBlock() const {
    return chain.back();
}

bool Blockchain::addTransaction(std::shared_ptr<Transaction> transaction) {
    // Se for recompensa de mineração, aceitar diretamente
    if (transaction->getType() == Transaction::Type::MINING_REWARD) {
        pendingTransactions.push_back(transaction);
        return true;
    }

    // Verificar se o remetente tem saldo suficiente
    double senderBalance = getBalance(transaction->getFromAddress());
    if (senderBalance < transaction->getAmount()) {
        return false; // Saldo insuficiente
    }

    // Adicionar à lista de transações pendentes
    pendingTransactions.push_back(transaction);
    return true;
}

void Blockchain::minePendingTransactions(const std::string& minerAddress) {
    // Criar bloco com as transações pendentes
    auto transactions = pendingTransactions;
    
    // Adicionar a recompensa de mineração
    auto rewardTx = std::make_shared<Transaction>(
        Transaction::Type::MINING_REWARD,
        "system",
        minerAddress,
        miningReward
    );
    transactions.push_back(rewardTx);
    
    // Criar e minerar o novo bloco
    Block newBlock(chain.size(), transactions, getLatestBlock().getHash());
    newBlock.mineBlock(difficulty);
    
    // Adicionar o bloco à chain
    chain.push_back(newBlock);
    
    // Limpar as transações pendentes
    pendingTransactions.clear();
}

double Blockchain::getBalance(const std::string& address) const {
    double balance = 0.0;
    
    // Calcular saldo baseado em todas as transações confirmadas
    for (const auto& block : chain) {
        for (const auto& tx : block.getTransactions()) {
            if (tx->getFromAddress() == address) {
                balance -= tx->getAmount();
            }
            if (tx->getToAddress() == address) {
                balance += tx->getAmount();
            }
        }
    }
    
    // Considerar também transações pendentes
    for (const auto& tx : pendingTransactions) {
        if (tx->getFromAddress() == address) {
            balance -= tx->getAmount();
        }
        if (tx->getToAddress() == address) {
            balance += tx->getAmount();
        }
    }
    
    return balance;
}

std::vector<std::shared_ptr<Transaction>> Blockchain::getTransactionHistory(const std::string& address) const {
    std::vector<std::shared_ptr<Transaction>> history;
    
    // Adicionar transações confirmadas
    for (const auto& block : chain) {
        for (const auto& tx : block.getTransactions()) {
            if (tx->getFromAddress() == address || tx->getToAddress() == address) {
                history.push_back(tx);
            }
        }
    }
    
    // Adicionar transações pendentes
    for (const auto& tx : pendingTransactions) {
        if (tx->getFromAddress() == address || tx->getToAddress() == address) {
            history.push_back(tx);
        }
    }
    
    return history;
}

bool Blockchain::isChainValid() const {
    for (size_t i = 1; i < chain.size(); i++) {
        const Block& currentBlock = chain[i];
        const Block& previousBlock = chain[i - 1];
        
        // Verificar hash do bloco
        if (currentBlock.getHash() != currentBlock.calculateHash()) {
            return false;
        }
        
        // Verificar conexão com o bloco anterior
        if (currentBlock.getPreviousHash() != previousBlock.getHash()) {
            return false;
        }
    }
    return true;
}
