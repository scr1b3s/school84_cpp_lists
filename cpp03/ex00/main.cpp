#include "ClapTrap.hpp"
#include <iostream>

int main() {
    ClapTrap clap1("CL4P-TP");
    ClapTrap clap2(clap1);
    ClapTrap clap3;
    clap3 = clap1;
    
    clap1.attack("bandit");
    clap1.takeDamage(5);
    clap1.beRepaired(3);
    clap1.takeDamage(10);
    clap1.attack("another bandit");
    
    return 0;
}