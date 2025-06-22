#include "Cat.hpp"

Cat::Cat() {
    type = "Cat";
    std::cout << "Cat constructor called" << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other) {
    std::cout << "Cat copy constructor called" << std::endl;
}

Cat::~Cat() {
    std::cout << "Cat destructor called" << std::endl;
}

Cat& Cat::operator=(const Cat& other) {
    Animal::operator=(other);
    return *this;
}

void Cat::makeSound() const {
    std::cout << "Meow meow!" << std::endl;
}