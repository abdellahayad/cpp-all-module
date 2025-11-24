#include "Intern.hpp"

Intern::Intern() {}

Intern::Intern(const Intern& copy){(void)copy;}

Intern &Intern::operator=(const Intern& other){(void)other; return *this;}

Intern::~Intern(){}

AForm* createShrubbery(const std::string& target)
{
    return new ShrubberyCreationForm(target);
}

AForm* createRobotomy(const std::string& target)
{
    return new RobotomyRequestForm(target);
}
AForm* createPresidential(const std::string& target)
{
    return new PresidentialPardonForm(target);
}




AForm *Intern::makeForm(const std::string& formName,  const std::string& target)
{
    std::string name[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};

    AForm* (*functions[3])(const std::string&) = {&createShrubbery, &createRobotomy, &createPresidential};
    
    for (int i = 0; i < 3; i++)
    {
        if (formName == name[i])
        {
            std::cout << "Intern create" <<  std::endl;
            return (functions[i])(target);
        }
    }
    std::cout << "Intern couldn't find the form" <<  std::endl;
    return NULL;
}