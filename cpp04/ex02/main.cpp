#include "Cat.hpp"
#include "Dog.hpp"

int main() {
    // These still work:
    Animal* dog = new Dog();
    Animal* cat = new Cat();

    dog->makeSound();
    cat->makeSound();

    delete dog;
    delete cat;
}