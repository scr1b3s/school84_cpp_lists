#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include <iostream>

int main() {
    std::cout << "===== CLAPTRAP TESTS =====" << std::endl;
    ClapTrap clap("CL4P-9000");
    clap.attack("Bandit");
    clap.takeDamage(5);
    clap.beRepaired(3);

    std::cout << "\n===== FRAGTRAP TESTS =====" << std::endl;
    FragTrap frag("FR4G-TP");
    frag.attack("Raider");
    frag.takeDamage(20);
    frag.beRepaired(10);
    frag.highFivesGuys();

    std::cout << "\n===== DESTRUCTORS =====" << std::endl;
    return 0;
}