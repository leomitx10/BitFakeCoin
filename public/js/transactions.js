document.addEventListener('DOMContentLoaded', () => {
    const token = localStorage.getItem('token');
    if (!token) {
        window.location.href = '/index.html';
        return;
    }

    const transactionForm = document.getElementById('transactionForm');
    const transactionList = document.getElementById('transactionList');
    let currentFilter = 'all';

    transactionForm.addEventListener('submit', async (e) => {
        e.preventDefault();
        
        const recipientAddress = document.getElementById('recipientAddress').value;
        const amount = parseFloat(document.getElementById('amount').value);

        try {
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

            if (response.ok) {
                alert('Transação enviada com sucesso!');
                transactionForm.reset();
                loadTransactions();
            } else {
                const error = await response.json();
                alert(error.message || 'Erro ao enviar transação');
            }
        } catch (error) {
            console.error('Erro:', error);
            alert('Erro ao enviar transação');
        }
    });

    // Filtros de transação
    document.querySelectorAll('.filter-btn').forEach(btn => {
        btn.addEventListener('click', () => {
            document.querySelectorAll('.filter-btn').forEach(b => b.classList.remove('active'));
            btn.classList.add('active');
            currentFilter = btn.dataset.filter;
            loadTransactions();
        });
    });

    async function loadTransactions() {
        try {
            const response = await fetch(`/api/transactions/history?filter=${currentFilter}`, {
                headers: {
                    'Authorization': `Bearer ${token}`
                }
            });

            if (response.ok) {
                const transactions = await response.json();
                displayTransactions(transactions);
            } else {
                alert('Erro ao carregar transações');
            }
        } catch (error) {
            console.error('Erro:', error);
        }
    }

    function displayTransactions(transactions) {
        transactionList.innerHTML = '';

        if (transactions.length === 0) {
            transactionList.innerHTML = '<p>Nenhuma transação encontrada.</p>';
            return;
        }

        transactions.forEach(tx => {
            const txElement = document.createElement('div');
            txElement.className = `transaction-item ${tx.type}`;
            
            const amount = tx.type === 'sent' ? `-${tx.amount}` : `+${tx.amount}`;
            const amountClass = tx.type === 'sent' ? 'text-danger' : 'text-success';

            txElement.innerHTML = `
                <div class="transaction-header">
                    <span class="transaction-type">${tx.type === 'sent' ? 'Enviado' : 'Recebido'}</span>
                    <span class="transaction-amount ${amountClass}">${amount} coins</span>
                </div>
                <div class="transaction-details">
                    <p><strong>${tx.type === 'sent' ? 'Para' : 'De'}:</strong> ${tx.type === 'sent' ? tx.to : tx.from}</p>
                    <p><strong>Data:</strong> ${new Date(tx.timestamp).toLocaleString()}</p>
                    <p><strong>Status:</strong> ${tx.status}</p>
                </div>
            `;

            transactionList.appendChild(txElement);
        });
    }

    // Carregar transações iniciais
    loadTransactions();
});
