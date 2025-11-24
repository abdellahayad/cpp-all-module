#ifndef PRESIDENTIALPARDONFORH_HPP
#define PRESIDENTIALPARDONFORH_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
    private:
        std::string target;

    public:
        PresidentialPardonForm(const std::string &target);
        PresidentialPardonForm(const PresidentialPardonForm& copy);
        PresidentialPardonForm &operator=(const PresidentialPardonForm& ohter);
        ~PresidentialPardonForm();

        void execute(Bureaucrat const &executor) const;
};

#endif
