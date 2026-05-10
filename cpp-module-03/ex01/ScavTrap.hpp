#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{
    private:
        bool guardMode;
    public:
        ScavTrap();
        ScavTrap(std::string name);
        ScavTrap(const ScavTrap &copy);
        ScavTrap &operator=(const ScavTrap &other);
        ~ScavTrap();

        void attack(const std::string &target);
        void guardGate();
};

#endif