#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "Transaction.h"

class TransactionPool {
private:
    std::vector<std::shared_ptr<Transaction>> pendingTransactions;
    std::unordered_map<std::string, double> balances;

public:
    bool addTransaction(std::shared_ptr<Transaction> transaction) {
        // Se for recompensa de mineração ou o primeiro bloco, aceitar direto
        if (transaction->getType() == Transaction::Type::MINING_REWARD) {
            pendingTransactions.push_back(transaction);
            balances[transaction->getToAddress()] += transaction->getAmount();
            return true;
        }

        // Calcular saldo atual do remetente
        double senderBalance = balances[transaction->getFromAddress()];
        
        // Verificar se há saldo suficiente
        if (senderBalance < transaction->getAmount()) {
            return false;
        }
        
        // Atualizar os saldos
        balances[transaction->getFromAddress()] -= transaction->getAmount();
        balances[transaction->getToAddress()] += transaction->getAmount();
        
        pendingTransactions.push_back(transaction);
        return true;
    }

    const std::vector<std::shared_ptr<Transaction>>& getPendingTransactions() const {
        return pendingTransactions;
    }

    void clearPendingTransactions() {
        pendingTransactions.clear();
    }

    double getBalance(const std::string& address) const {
        auto it = balances.find(address);
        return it != balances.end() ? it->second : 0.0;
    }

    void updateBalance(const std::string& address, double amount) {
        balances[address] = amount;
    }
};
