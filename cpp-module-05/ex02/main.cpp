#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
    try
    {
        Bureaucrat abdellah("Abdellah", 1);
        Bureaucrat omar("Omar", 140);

        ShrubberyCreationForm f1("home");
        RobotomyRequestForm f2("dorms");
        PresidentialPardonForm f3("1337");

        std::cout << "====== Signing ======" << std::endl;
        abdellah.signForm(f1);
        abdellah.signForm(f2);
        abdellah.signForm(f3);
        omar.signForm(f2);

        std::cout << "====== Executing ======" << std::endl;
        abdellah.executeForm(f1);
        abdellah.executeForm(f2);
        abdellah.executeForm(f3);
        omar.executeForm(f2);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}
