#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& t)
    : AForm("ShrubberyCreationForm", 145, 137), target(t) {}


ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& copy) : AForm(copy), target(copy.target) {}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
    if (this != &other)
        target = other.target;
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}




void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
    if (!getIsSigned())
        throw FormNotSignedException();
    if (executor.getGrade() > getGradeToExecute())
        throw GradeTooLowException();

    std::ofstream file((target + "_shrubbery").c_str());
    file << "       *\n";
    file << "      ***\n";
    file << "     *****\n";
    file << "    *******\n";
    file << "   *********\n";
    file << "  ***********\n";
    file << " *************\n";
    file << "***************\n";
    file << "      |||\n";
    file << "      |||\n";
    file << "\n";

    file.close();
}