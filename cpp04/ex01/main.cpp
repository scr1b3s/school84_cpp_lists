#include "Dog.hpp"
#include "Cat.hpp"
#include <iostream>

int main() {
    std::cout << "===== CONSTRUCTION TEST =====" << std::endl;
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << "\n===== DESTRUCTION TEST =====" << std::endl;
    delete j;
    delete i;

    std::cout << "\n===== ARRAY OF ANIMALS TEST =====" << std::endl;
    Animal* animals[4];
    for (int k = 0; k < 2; ++k) animals[k] = new Dog();
    for (int k = 2; k < 4; ++k) animals[k] = new Cat();
    for (int k = 0; k < 4; ++k) delete animals[k];

    std::cout << "\n===== DEEP COPY TEST =====" << std::endl;
    Dog originalDog;
    originalDog.getBrain()->setIdea(0, "Chase the cat!");
    Dog copiedDog = originalDog; // Deep copy

    std::cout << "Original Dog's idea: " << originalDog.getBrain()->getIdea(0) << std::endl;
    std::cout << "Copied Dog's idea: " << copiedDog.getBrain()->getIdea(0) << std::endl;

    copiedDog.getBrain()->setIdea(0, "Squirrel?");
    std::cout << "After modification:" << std::endl;
    std::cout << "Original Dog's idea: " << originalDog.getBrain()->getIdea(0) << std::endl;
    std::cout << "Copied Dog's idea: " << copiedDog.getBrain()->getIdea(0) << std::endl;

    std::cout << "\n===== END OF TESTS =====" << std::endl;
    return 0;
}