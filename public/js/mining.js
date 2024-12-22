document.addEventListener('DOMContentLoaded', () => {
    const token = localStorage.getItem('token');
    if (!token) {
        window.location.href = '/index.html';
        return;
    }

    const startMiningBtn = document.getElementById('startMining');
    const stopMiningBtn = document.getElementById('stopMining');
    const miningStatus = document.getElementById('miningStatus');
    const blocksMined = document.getElementById('blocksMined');
    const totalRewards = document.getElementById('totalRewards');
    const miningLog = document.getElementById('miningLog');

    let isMining = false;
    let miningInterval;

    startMiningBtn.addEventListener('click', async () => {
        try {
            const response = await fetch('/api/mining/start', {
                method: 'POST',
                headers: {
                    'Authorization': `Bearer ${token}`
                }
            });

            if (response.ok) {
                isMining = true;
                startMiningBtn.disabled = true;
                stopMiningBtn.disabled = false;
                miningStatus.textContent = 'Minerando';
                startMiningProcess();
            } else {
                alert('Erro ao iniciar mineração');
            }
        } catch (error) {
            console.error('Erro:', error);
        }
    });

    stopMiningBtn.addEventListener('click', async () => {
        try {
            const response = await fetch('/api/mining/stop', {
                method: 'POST',
                headers: {
                    'Authorization': `Bearer ${token}`
                }
            });

            if (response.ok) {
                isMining = false;
                startMiningBtn.disabled = false;
                stopMiningBtn.disabled = true;
                miningStatus.textContent = 'Parado';
                clearInterval(miningInterval);
            } else {
                alert('Erro ao parar mineração');
            }
        } catch (error) {
            console.error('Erro:', error);
        }
    });

    function startMiningProcess() {
        miningInterval = setInterval(async () => {
            if (!isMining) return;

            try {
                const response = await fetch('/api/mining/status', {
                    headers: {
                        'Authorization': `Bearer ${token}`
                    }
                });

                if (response.ok) {
                    const data = await response.json();
                    blocksMined.textContent = data.blocksMined;
                    totalRewards.textContent = data.totalRewards.toFixed(2);

                    if (data.lastBlockMined) {
                        addToMiningLog(`Bloco minerado! Hash: ${data.lastBlockMined.hash.substring(0, 10)}...`);
                    }
                }
            } catch (error) {
                console.error('Erro ao atualizar status da mineração:', error);
            }
        }, 5000);
    }

    function addToMiningLog(message) {
        const logEntry = document.createElement('p');
        logEntry.textContent = `[${new Date().toLocaleTimeString()}] ${message}`;
        miningLog.insertBefore(logEntry, miningLog.firstChild);

        // Limitar o número de entradas no log
        if (miningLog.children.length > 50) {
            miningLog.removeChild(miningLog.lastChild);
        }
    }
});
