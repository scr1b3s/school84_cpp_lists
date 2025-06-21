#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int main() {
    ClapTrap clap("CL4P-TP");
    clap.attack("bandit");
    clap.takeDamage(5);
    clap.beRepaired(3);
    
    ScavTrap scav("SC4V-TP");
    scav.attack("raider");
    scav.takeDamage(30);
    scav.beRepaired(10);
    scav.guardGate();
    
    return 0;
}