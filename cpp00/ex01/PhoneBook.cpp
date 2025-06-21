#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

PhoneBook::PhoneBook() : contactCount(0) {}

void PhoneBook::addContact() {
    if (contactCount == 8)
        contactCount = 0;
    contacts[contactCount].setContact();
    contactCount++;
}

void PhoneBook::searchContacts() const {
    std::cout << std::setw(10) << "Index" << "|"
              << std::setw(10) << "First Name" << "|"
              << std::setw(10) << "Last Name" << "|"
              << std::setw(10) << "Nickname" << std::endl;

    for (int i = 0; i < contactCount; i++) {
        contacts[i].displayContact(i);
    }

    std::cout << "Enter index to view details: ";
    std::string input;
    std::getline(std::cin, input);
    
    std::istringstream iss(input);
    int index;
    iss >> index;

    if (index >= 0 && index < contactCount) {
        contacts[index].displayFullContact();
    } else {
        std::cout << "Invalid index!" << std::endl;
    }
}
