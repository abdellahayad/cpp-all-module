#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(const std::string& t)
    : AForm("RobotomyRequestForm", 72, 45), target(t) {}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& copy) : AForm(copy), target(copy.target) {}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm& other)
{
    if (this != &other)
    {
        target = other.target;
    }
    return *this;
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
    static bool rand = false;

    if (!getIsSigned())
        throw FormNotSignedException();
    if (executor.getGrade() > getGradeToExecute())
        throw GradeTooLowException();

    std::cout << "Bzzzzz... drilling noises..." << std::endl;
    
    if (rand)
        std::cout << target << " has been robotomized successfully!" << std::endl;
    else
        std::cout << target << " robotomy failed." << std::endl;

    rand = !rand;
}