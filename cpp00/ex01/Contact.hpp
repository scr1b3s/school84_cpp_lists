#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact {
private:
    std::string firstName;
    std::string lastName;
    std::string nickname;
    std::string phoneNumber;
    std::string darkestSecret;

public:
    void setContact();
    void displayContact(int index) const;
    void displayFullContact() const;
    
private:
    void printField(const std::string& field) const;
};

#endif
