document.addEventListener('DOMContentLoaded', function() {
    const menuToggle = document.getElementById('menuToggle');
    const navMenu = document.getElementById('navMenu');
    const userMenuBtn = document.getElementById('userMenuBtn');
    const userDropdown = document.getElementById('userDropdown');

    // Toggle mobile menu
    menuToggle.addEventListener('click', function() {
        navMenu.classList.toggle('show');
    });

    // Close mobile menu when clicking outside
    document.addEventListener('click', function(event) {
        if (!navMenu.contains(event.target) && !menuToggle.contains(event.target)) {
            navMenu.classList.remove('show');
        }
    });

    // User dropdown toggle
    userMenuBtn.addEventListener('click', function(event) {
        event.stopPropagation();
        userDropdown.classList.toggle('show');
    });

    // Close user dropdown when clicking outside
    document.addEventListener('click', function(event) {
        if (!userDropdown.contains(event.target) && !userMenuBtn.contains(event.target)) {
            userDropdown.classList.remove('show');
        }
    });

    // Handle window resize
    window.addEventListener('resize', function() {
        if (window.innerWidth > 768) {
            navMenu.classList.remove('show');
            userDropdown.classList.remove('show');
        }
    });
});
