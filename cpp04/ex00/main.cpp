#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

int main()
{
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << "j type: " << j->getType() << std::endl;
    std::cout << "i type: " << i->getType() << std::endl;
    i->makeSound();
    j->makeSound();
    meta->makeSound();

    delete meta;
    delete j;
    delete i;

    std::cout << "\n=== WrongAnimal Polymorphism Test ===" << std::endl;
    const WrongAnimal* wrongMeta = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();

    std::cout << "wrongCat type: " << wrongCat->getType() << std::endl;
    wrongCat->makeSound();
    wrongMeta->makeSound();

    delete wrongMeta;
    delete wrongCat;

    std::cout << "\n=== Direct WrongCat Test ===" << std::endl;
    WrongCat realWrongCat;
    realWrongCat.makeSound();

    std::cout << "\n=== Copy and Assignment Test ===" << std::endl;
    Dog dog1;
    Dog dog2 = dog1;
    Dog dog3;
    dog3 = dog1;

    Cat cat1;
    Cat cat2 = cat1;
    Cat cat3;
    cat3 = cat1;

    WrongCat wrongCat1;
    WrongCat wrongCat2 = wrongCat1;
    WrongCat wrongCat3;
    wrongCat3 = wrongCat1;

    std::cout << "\n=== Slicing Test ===" << std::endl;
    Animal animalCat = Cat();
    animalCat.makeSound();

    return 0;
}