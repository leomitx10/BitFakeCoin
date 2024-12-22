document.addEventListener('DOMContentLoaded', () => {
    const token = sessionStorage.getItem('token');
    if (!token) {
        window.location.href = 'login.html';
        return;
    }

    const startMiningBtn = document.getElementById('startMining');
    const stopMiningBtn = document.getElementById('stopMining');
    const miningStatus = document.getElementById('miningStatus');
    const blocksMined = document.getElementById('blocksMined');
    const totalRewards = document.getElementById('totalRewards');
    const miningLog = document.getElementById('miningLog');
    
    let isMining = false;

    startMiningBtn.addEventListener('click', async () => {
        if (isMining) return;

        try {
            isMining = true;
            startMiningBtn.disabled = true;
            stopMiningBtn.disabled = false;
            miningStatus.textContent = 'Minerando...';

            const response = await fetch('/api/mining/start', {
                method: 'POST',
                headers: {
                    'Authorization': `Bearer ${sessionStorage.getItem('token')}`
                }
            });

            if (!response.ok) {
                throw new Error('Falha ao iniciar mineração');
            }

            const result = await response.json();
            addToMiningLog(`Bloco minerado com sucesso! Hash: ${result.hash}`);
            
            // Atualizar estatísticas
            const currentBlocks = parseInt(blocksMined.textContent) || 0;
            blocksMined.textContent = (currentBlocks + 1).toString();
            
            // Atualizar recompensas (50 BFC por bloco)
            const currentRewards = parseFloat(totalRewards.textContent) || 0;
            totalRewards.textContent = (currentRewards + 50).toFixed(2);
            
            // Atualizar o saldo
            updateBalance();
            
            // Resetar estado
            isMining = false;
            startMiningBtn.disabled = false;
            stopMiningBtn.disabled = true;
            miningStatus.textContent = 'Pronto para minerar';
            
        } catch (error) {
            console.error('Erro:', error);
            miningStatus.textContent = 'Erro ao minerar. Tente novamente.';
            isMining = false;
            startMiningBtn.disabled = false;
            stopMiningBtn.disabled = true;
            addToMiningLog('Erro ao minerar: ' + error.message);
        }
    });

    stopMiningBtn.addEventListener('click', () => {
        isMining = false;
        startMiningBtn.disabled = false;
        stopMiningBtn.disabled = true;
        miningStatus.textContent = 'Pronto para minerar';
    });

    // Atualizar saldo inicial
    updateBalance();
});

function addToMiningLog(message) {
    const date = new Date();
    const timestamp = date.toLocaleTimeString();
    const logEntry = document.createElement('div');
    logEntry.className = 'log-entry';
    logEntry.innerHTML = `
        <span class="log-time">[${timestamp}]</span>
        <span class="log-message">${message}</span>
    `;
    
    const miningLog = document.getElementById('miningLog');
    miningLog.insertBefore(logEntry, miningLog.firstChild);

    // Manter apenas os últimos 50 registros
    while (miningLog.children.length > 50) {
        miningLog.removeChild(miningLog.lastChild);
    }
}

async function updateBalance() {
    try {
        const response = await fetch('/api/transactions/history', {
            headers: {
                'Authorization': `Bearer ${sessionStorage.getItem('token')}`
            }
        });

        if (!response.ok) {
            throw new Error('Falha ao atualizar saldo');
        }

        const data = await response.json();
        const balanceElement = document.getElementById('balance');
        if (balanceElement) {
            balanceElement.textContent = `${data.balance.toFixed(2)} BFC`;
        }
    } catch (error) {
        console.error('Erro ao atualizar saldo:', error);
    }
}
