document.addEventListener('DOMContentLoaded', () => {
    const token = sessionStorage.getItem('token');
    if (!token) {
        window.location.href = 'index.html';
        return;
    }

    loadDashboard();
    
    // Configurar o menu dropdown do usuário
    const userMenuBtn = document.getElementById('userMenuBtn');
    const userDropdown = document.getElementById('userDropdown');
    
    userMenuBtn.addEventListener('click', (e) => {
        e.stopPropagation();
        userDropdown.classList.toggle('show');
    });

    // Fechar o dropdown quando clicar fora dele
    document.addEventListener('click', (e) => {
        if (!userDropdown.contains(e.target) && !userMenuBtn.contains(e.target)) {
            userDropdown.classList.remove('show');
        }
    });
    
    // Configurar o logout
    document.getElementById('logoutBtn').addEventListener('click', (e) => {
        e.preventDefault();
        sessionStorage.removeItem('token');
        window.location.href = 'index.html';
    });
});

async function loadDashboard() {
    try {
        const token = sessionStorage.getItem('token');
        const response = await fetch('/api/transactions/history', {
            headers: {
                'Authorization': `Bearer ${token}`
            }
        });

        if (!response.ok) {
            throw new Error('Falha ao carregar dados');
        }

        const data = await response.json();
        
        // Atualizar saldo e endereço
        document.getElementById('balance').textContent = `${data.balance.toFixed(2)} BFC`;
        document.getElementById('walletAddress').textContent = data.address;

        // Atualizar histórico de transações
        const transactionList = document.getElementById('transactionList');
        transactionList.innerHTML = '';

        if (data.transactions.length === 0) {
            transactionList.innerHTML = '<p>Nenhuma transação encontrada.</p>';
            return;
        }

        // Inverter a ordem e mostrar apenas as 5 transações mais recentes
        const sortedTransactions = [...data.transactions].reverse();
        const recentTransactions = sortedTransactions.slice(0, 5);
        recentTransactions.forEach(transaction => {
            const card = createTransactionCard(transaction);
            transactionList.appendChild(card);
        });

    } catch (error) {
        console.error('Erro:', error);
        document.getElementById('balance').textContent = 'Erro ao carregar';
        document.getElementById('walletAddress').textContent = 'Erro ao carregar';
        document.getElementById('transactionList').innerHTML = 
            '<p>Erro ao carregar transações. Tente novamente mais tarde.</p>';
    }
}

function createTransactionCard(transaction) {
    const card = document.createElement('div');
    let iconClass, cardClass, title, info;
    
    // Determinar o tipo de card baseado no tipo de transação
    if (transaction.type === 'mining_reward') {
        iconClass = 'fa-coins';
        cardClass = 'mining-reward';
        title = 'Recompensa de Mineração';
        info = `Bloco #${transaction.blockNumber}`;
    } else if (transaction.direction === 'sent') {
        iconClass = 'fa-arrow-up';
        cardClass = 'sent-transaction';
        title = 'Enviado';
        info = `Para: ${transaction.to}`;
    } else {
        iconClass = 'fa-arrow-down';
        cardClass = 'received-transaction';
        title = 'Recebido';
        info = `De: ${transaction.from}`;
    }

    // Formatar data e hora
    const date = new Date(transaction.timestamp);
    const formattedDate = date.toLocaleDateString('pt-BR');
    const formattedTime = date.toLocaleTimeString('pt-BR', { 
        hour: '2-digit', 
        minute: '2-digit' 
    });

    // Formatar valor com sinal
    const sign = transaction.impact >= 0 ? '+' : '';
    const amount = `${sign}${transaction.impact.toFixed(2)} BFC`;

    // Criar HTML do card
    card.className = `transaction-card ${cardClass} dashboard-card`;
    card.innerHTML = `
        <div class="transaction-icon">
            <i class="fas ${iconClass}"></i>
        </div>
        <div class="transaction-content">
            <div class="transaction-title">${title}</div>
            <div class="transaction-info">${info}</div>
        </div>
        <div class="transaction-timestamp">${formattedDate} ${formattedTime}</div>
        <div class="transaction-amount">${amount}</div>
    `;

    return card;
}

// Função para copiar o endereço da carteira
function copyAddress() {
    const address = document.getElementById('walletAddress').textContent;
    navigator.clipboard.writeText(address).then(() => {
        alert('Endereço copiado para a área de transferência!');
    }).catch(err => {
        console.error('Erro ao copiar:', err);
        alert('Erro ao copiar endereço');
    });
}
