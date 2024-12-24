class Navbar extends HTMLElement {
    constructor() {
        super();
    }

    connectedCallback() {
        this.innerHTML = `
            <nav class="navbar">
                <div class="nav-brand">
                    <i class="fas fa-coins"></i>
                    CryptoProject
                </div>
                <button class="menu-toggle" id="menuToggle">
                    <i class="fas fa-bars"></i>
                </button>
                <div class="nav-menu" id="navMenu">
                    <a href="dashboard.html" ${window.location.pathname.includes('dashboard') ? 'class="active"' : ''}>Dashboard</a>
                    <a href="mining.html" ${window.location.pathname.includes('mining') ? 'class="active"' : ''}>Mineração</a>
                    <a href="transactions.html" ${window.location.pathname.includes('transactions') ? 'class="active"' : ''}>Transações</a>
                    <div class="user-menu">
                        <i class="fas fa-user user-icon" id="userMenuBtn"></i>
                        <div class="dropdown-menu" id="userDropdown">
                            <a href="#" id="logoutBtn">Sair</a>
                        </div>
                    </div>
                </div>
            </nav>
        `;

        // Initialize menu functionality
        this.initializeMenu();
    }

    initializeMenu() {
        const menuToggle = this.querySelector('#menuToggle');
        const navMenu = this.querySelector('#navMenu');
        const userMenuBtn = this.querySelector('#userMenuBtn');
        const userDropdown = this.querySelector('#userDropdown');
        const logoutBtn = this.querySelector('#logoutBtn');

        // Initialize dropdown state
        let isDropdownOpen = false;

        // Mobile menu toggle
        if (menuToggle && navMenu) {
            menuToggle.addEventListener('click', (event) => {
                event.stopPropagation();
                navMenu.classList.toggle('show');
            });
        }

        // User dropdown toggle
        if (userMenuBtn && userDropdown) {
            userMenuBtn.addEventListener('click', (event) => {
                event.preventDefault();
                event.stopPropagation();
                
                isDropdownOpen = !isDropdownOpen;
                if (isDropdownOpen) {
                    userDropdown.classList.add('show');
                } else {
                    userDropdown.classList.remove('show');
                }
            });
        }

        // Close dropdowns when clicking outside
        document.addEventListener('click', (event) => {
            const isClickInsideUserMenu = userMenuBtn && userMenuBtn.contains(event.target);
            const isClickInsideDropdown = userDropdown && userDropdown.contains(event.target);
            
            if (!isClickInsideUserMenu && !isClickInsideDropdown && isDropdownOpen) {
                userDropdown.classList.remove('show');
                isDropdownOpen = false;
            }

            if (navMenu && 
                navMenu.classList.contains('show') && 
                !navMenu.contains(event.target) && 
                !menuToggle.contains(event.target)) {
                navMenu.classList.remove('show');
            }
        });

        // Handle logout
        if (logoutBtn) {
            logoutBtn.addEventListener('click', (event) => {
                event.preventDefault();
                sessionStorage.removeItem('token');
                window.location.href = 'index.html';
            });
        }

        // Handle window resize
        window.addEventListener('resize', () => {
            if (window.innerWidth > 768) {
                if (navMenu) navMenu.classList.remove('show');
                if (userDropdown) {
                    userDropdown.classList.remove('show');
                    isDropdownOpen = false;
                }
            }
        });
    }
}

// Register the custom element
customElements.define('nav-bar', Navbar);
