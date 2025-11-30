#include "Character.hpp"

Character::Character(const std::string& name) : name(name), trash(NULL)
{
    for (int i = 0; i < 4; i++)
        inventory[i] = NULL;
}

Character::Character(const Character& copy) : name(copy.name)
{
    for (int i = 0; i < 4; i++)
    {
        if (copy.inventory[i])
            inventory[i] = copy.inventory[i]->clone();
        else
            inventory[i] = NULL;
    }
}

Character &Character::operator=(const Character& other) 
{

    if (this != &other)
        name = other.name;
    for (int i = 0; i < 4; i++)
    {
        if (inventory[i])
        {
            delete inventory[i];
            inventory[i] = NULL;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (other.inventory[i])
            inventory[i] = other.inventory[i]->clone();
        else
            inventory[i] = NULL;
    }
    return *this;
}

Character::~Character()
{
    for (int i = 0; i < 4; i++)
    {
        if (inventory[i])
        {
            delete inventory[i];
            inventory[i] = NULL;
        }
    }

    while (trash)
    {
        node *tmp = trash;
        trash = trash->next;
        delete tmp->materia;
        delete tmp;
    }
}

std::string const& Character::getName() const{return name;}

void Character::equip(AMateria *m)
{
    if (!m)
        return ;
    for (int i = 0; i < 4; i++)
    {
        if (!inventory[i])
        {
            inventory[i] = m;
            return ;
        }
    }
    delete m;
}

void Character::unequip(int idx)
{
    if (idx < 0 || idx >= 4 || inventory[idx])
        return ;

    node *newnode = new node;
    newnode->materia = inventory[idx];
    newnode->next = trash;
    trash = newnode;

    inventory[idx] = NULL;
}

void Character::use(int idx, ICharacter& target)
{
    if (idx < 0 || idx >= 4)
        return ;
    if (inventory[idx])
        inventory[idx]->use(target);
}