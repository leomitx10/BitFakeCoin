document.addEventListener('DOMContentLoaded', () => {
    const token = sessionStorage.getItem('token');
    if (!token) {
        window.location.href = 'login.html';
        return;
    }

    loadTransactions();
    setupTransactionForm();
    setupFilterButtons();
});

async function loadTransactions() {
    try {
        const token = sessionStorage.getItem('token');
        if (!token) {
            window.location.href = 'login.html';
            return;
        }

        const response = await fetch('/api/transactions/history', {
            headers: {
                'Authorization': `Bearer ${token}`
            }
        });

        if (!response.ok) {
            throw new Error('Falha ao carregar transações');
        }

        const data = await response.json();
        const transactionList = document.getElementById('transactionList');
        transactionList.innerHTML = '';

        if (data.transactions.length === 0) {
            transactionList.innerHTML = '<p>Nenhuma transação encontrada.</p>';
            return;
        }

        // Inverter a ordem para mostrar as mais recentes primeiro
        const sortedTransactions = [...data.transactions].reverse();
        sortedTransactions.forEach(transaction => {
            const card = createTransactionCard(transaction);
            transactionList.appendChild(card);
        });
    } catch (error) {
        console.error('Erro:', error);
        document.getElementById('transactionList').innerHTML = 
            '<p>Erro ao carregar transações. Tente novamente mais tarde.</p>';
    }
}

function setupTransactionForm() {
    const form = document.getElementById('transactionForm');
    form.addEventListener('submit', async (e) => {
        e.preventDefault();
        
        const recipientAddress = document.getElementById('recipientAddress').value;
        const amount = parseFloat(document.getElementById('amount').value);
        
        try {
            const token = sessionStorage.getItem('token');
            const response = await fetch('/api/transactions/send', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': `Bearer ${token}`
                },
                body: JSON.stringify({
                    to: recipientAddress,
                    amount: amount
                })
            });

            if (!response.ok) {
                const error = await response.json();
                throw new Error(error.message || 'Falha ao enviar transação');
            }

            alert('Transação enviada com sucesso!');
            form.reset();
            loadTransactions();
        } catch (error) {
            alert(error.message);
        }
    });
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
    card.className = `transaction-card ${cardClass}`;
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

function setupFilterButtons() {
    const filterButtons = document.querySelectorAll('.filter-btn');
    filterButtons.forEach(button => {
        button.addEventListener('click', () => {
            // Remover classe active de todos os botões
            filterButtons.forEach(btn => btn.classList.remove('active'));
            button.classList.add('active');

            const filter = button.dataset.filter;
            const cards = document.querySelectorAll('.transaction-card');

            cards.forEach(card => {
                if (filter === 'all') {
                    card.style.display = 'flex';
                } else if (filter === 'sent') {
                    card.style.display = card.classList.contains('sent-transaction') ? 'flex' : 'none';
                } else if (filter === 'received') {
                    card.style.display = 
                        (card.classList.contains('received-transaction') || 
                         card.classList.contains('mining-reward')) ? 'flex' : 'none';
                }
            });
        });
    });
}
