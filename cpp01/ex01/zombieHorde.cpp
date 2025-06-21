#include "Zombie.hpp"
#include <sstream> 

Zombie* zombieHorde(int N, std::string name) {
    if (N <= 0)
        return 0;
    Zombie* horde = new Zombie[N];
    for (int i = 0; i < N; i++) {
        std::ostringstream oss;
        oss << name << " " << i;
        horde[i].setName(oss.str());
    }
    return horde;
}