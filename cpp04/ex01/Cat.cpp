#include "Cat.hpp"

Cat::Cat() : Animal() {
    type = "Cat";
    brain = new Brain();
    std::cout << "Cat constructor called" << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other) {
    brain = new Brain(*other.brain);
    std::cout << "Cat copy constructor called" << std::endl;
}

Cat::~Cat() {
    delete brain;
    std::cout << "Cat destructor called" << std::endl;
}

Cat& Cat::operator=(const Cat& other) {
    if (this != &other) {
        Animal::operator=(other);
        if (brain)
            delete brain;
        brain = new Brain(*other.brain);
    }
    return *this;
}

void Cat::makeSound() const {
    std::cout << "Meow meow!" << std::endl;
}

Brain* Cat::getBrain() const {
    return brain;
}