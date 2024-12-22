document.addEventListener('DOMContentLoaded', () => {
    const token = localStorage.getItem('token');
    if (!token) {
        window.location.href = '/index.html';
        return;
    }

    document.getElementById('logoutBtn').addEventListener('click', () => {
        localStorage.removeItem('token');
        window.location.href = '/index.html';
    });

    async function loadWalletInfo() {
        try {
            const response = await fetch('/api/wallet/info', {
                headers: {
                    'Authorization': `Bearer ${token}`
                }
            });

            if (response.ok) {
                const data = await response.json();
                document.getElementById('balance').textContent = `${data.balance} coins`;
                document.getElementById('walletAddress').textContent = data.address;
            } else {
                alert('Erro ao carregar informações da carteira');
            }
        } catch (error) {
            console.error('Erro:', error);
        }
    }

    async function loadTransactions() {
        try {
            const response = await fetch('/api/transactions/history', {
                headers: {
                    'Authorization': `Bearer ${token}`
                }
            });

            if (response.ok) {
                const data = await response.json();
                const transactions = data.transactions;
                const transactionList = document.getElementById('transactionList');
                transactionList.innerHTML = '';

                if (transactions.length === 0) {
                    transactionList.innerHTML = '<p class="no-transactions">Nenhuma transação encontrada.</p>';
                    return;
                }

                transactions.forEach(tx => {
                    const txElement = document.createElement('div');
                    txElement.className = `transaction-item ${tx.type}`;
                    
                    let amountText = '';
                    let addressText = '';
                    
                    switch (tx.type) {
                        case 'send':
                            amountText = `-${tx.amount}`;
                            addressText = `Para: ${tx.to}`;
                            break;
                        case 'receive':
                            amountText = `+${tx.amount}`;
                            addressText = `De: ${tx.from}`;
                            break;
                        case 'mining_reward':
                            amountText = `+${tx.amount}`;
                            addressText = 'Recompensa de Mineração';
                            break;
                    }

                    const date = new Date(tx.timestamp);
                    
                    txElement.innerHTML = `
                        <div class="transaction-header">
                            <span class="transaction-type">${tx.type === 'send' ? 'Enviado' : tx.type === 'receive' ? 'Recebido' : 'Mineração'}</span>
                            <span class="transaction-amount ${tx.type === 'send' ? 'text-danger' : 'text-success'}">${amountText} coins</span>
                        </div>
                        <div class="transaction-details">
                            <p>${addressText}</p>
                            <p>Data: ${date.toLocaleString()}</p>
                        </div>
                    `;

                    transactionList.appendChild(txElement);
                });
            } else {
                alert('Erro ao carregar transações');
            }
        } catch (error) {
            console.error('Erro:', error);
        }
    }

    // Atualizar informações a cada 30 segundos
    loadWalletInfo();
    loadTransactions();
    setInterval(() => {
        loadWalletInfo();
        loadTransactions();
    }, 30000);
});
