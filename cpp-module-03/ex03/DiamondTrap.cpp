#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
{
    name = "Unknown";
    ClapTrap::name = "default_clap_name";
    hitPoints = FragTrap::hitPoints;
    energyPoints = ScavTrap::energyPoints;
    attackDamage = FragTrap::attackDamage;
    std::cout << "DiamondTrap " << name << " created(default)." << std::endl;
}

DiamondTrap::DiamondTrap(std::string _name) 
{
    name = _name;
    ClapTrap::name = name + "_clap_name";
    hitPoints = FragTrap::hitPoints;
    energyPoints = ScavTrap::energyPoints;
    attackDamage = FragTrap::attackDamage;
    std::cout << "DiamondTrap " << name << " created." << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& copy)
            : ClapTrap(copy), FragTrap(copy), ScavTrap(copy)
{
    *this = copy;
    std::cout << "DiamondTrap " << name << " copied." << std::endl;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &other)
{
    if (this != &other)
    {
        hitPoints = other.hitPoints;
        energyPoints = other.energyPoints;
        attackDamage = other.attackDamage;
        name = other.name;
        ClapTrap::name = other.ClapTrap::name;
        std::cout << "DiamondTrap " << name << " assigned." << std::endl;
    }
    return *this;
}

DiamondTrap::~DiamondTrap()
{
    std::cout << "DiamondTrap " << name << " destroyed." << std::endl;
}

void DiamondTrap::attack(const std::string& target)
{
    ScavTrap::attack(target);
}

void DiamondTrap::whoAmI()
{
    std::cout << "DiamondTrap name is " << name << std::endl;
    std::cout << "ClapTrap name is " << ClapTrap::name << std::endl;
}
