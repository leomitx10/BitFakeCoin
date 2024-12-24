document.addEventListener('DOMContentLoaded', function() {
    const menuToggle = document.getElementById('menuToggle');
    const navMenu = document.getElementById('navMenu');
    const userMenuBtn = document.getElementById('userMenuBtn');
    const userDropdown = document.getElementById('userDropdown');
    const logoutBtn = document.getElementById('logoutBtn');

    // Initialize dropdown state
    let isDropdownOpen = false;

    // Mobile menu toggle
    if (menuToggle && navMenu) {
        menuToggle.addEventListener('click', function(event) {
            event.stopPropagation();
            navMenu.classList.toggle('show');
        });
    }

    // User dropdown toggle
    if (userMenuBtn && userDropdown) {
        userMenuBtn.addEventListener('click', function(event) {
            event.preventDefault();
            event.stopPropagation();
            
            // Toggle dropdown state
            isDropdownOpen = !isDropdownOpen;
            
            // Update dropdown visibility
            if (isDropdownOpen) {
                userDropdown.classList.add('show');
            } else {
                userDropdown.classList.remove('show');
            }
        });
    }

    // Close dropdowns when clicking outside
    document.addEventListener('click', function(event) {
        const isClickInsideUserMenu = userMenuBtn && userMenuBtn.contains(event.target);
        const isClickInsideDropdown = userDropdown && userDropdown.contains(event.target);
        
        // If click is outside both the user menu and dropdown
        if (!isClickInsideUserMenu && !isClickInsideDropdown && isDropdownOpen) {
            userDropdown.classList.remove('show');
            isDropdownOpen = false;
        }

        // Close mobile menu if clicking outside
        if (navMenu && 
            navMenu.classList.contains('show') && 
            !navMenu.contains(event.target) && 
            !menuToggle.contains(event.target)) {
            navMenu.classList.remove('show');
        }
    });

    // Handle logout
    if (logoutBtn) {
        logoutBtn.addEventListener('click', function(event) {
            event.preventDefault();
            sessionStorage.removeItem('token');
            window.location.href = 'index.html';
        });
    }

    // Handle window resize
    window.addEventListener('resize', function() {
        if (window.innerWidth > 768) {
            if (navMenu) navMenu.classList.remove('show');
            if (userDropdown) {
                userDropdown.classList.remove('show');
                isDropdownOpen = false;
            }
        }
    });
});
