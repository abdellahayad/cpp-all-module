#include "Zombie.hpp"

Zombie::Zombie() {};

Zombie::~Zombie()
{
    std::cout << name << " is destroyed" << std::endl;
}
void Zombie::annonce(void)
{
    std::cout << name << " : BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setName(std::string newNmae)
{
    name = newNmae;
}
