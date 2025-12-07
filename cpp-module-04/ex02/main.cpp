#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"
#include <string>

int main()
{
    const AAnimal* j = new Dog();
    const AAnimal* i = new Cat();


    j->makeSound();
    i->makeSound();
    
    delete j;
    delete i;

    std::cout << "\n--- Array test ---" << std::endl;
    AAnimal* AAnimals[4];

    std::cout << "==========================="  << std::endl;
    for (int k = 0; k < 4; k++) {
        if (k < 2)
        AAnimals[k] = new Dog();
        else
        AAnimals[k] = new Cat();
    }
    
    for (int k = 0; k < 4; k++)
        delete AAnimals[k];
    std::cout << "==========================="  << std::endl;

    std::cout << "\n--- Deep copy test ---" << std::endl;
    Dog dog1;

    dog1.getBrain()->setIdea(0, "i need to sleep");
    Dog dog2 = dog1;

    std::cout << "dog1 idea" << dog1.getBrain()->getIdea(0) << std::endl;
    std::cout << "dog2 idea" << dog2.getBrain()->getIdea(0) << std::endl;
    
    dog2.getBrain()->setIdea(0, "i need to eat");


    std::cout << "dog1 idea" << dog1.getBrain()->getIdea(0) << std::endl;
    std::cout << "dog2 idea" << dog2.getBrain()->getIdea(0) << std::endl;

    return 0;
}