#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie() : name("") {}

Zombie::Zombie(std::string name) : name(name) {}

Zombie::~Zombie() {
    if (!name.empty()) {
        std::cout << name << " has been destroyed." << std::endl;
    }
}

void Zombie::announce(void) {
    if (!name.empty()) {
        std::cout << name << ": BraiiiiinnnzzzZ..." << std::endl;
    }
}

void Zombie::setName(std::string name) {
    this->name = name;
}