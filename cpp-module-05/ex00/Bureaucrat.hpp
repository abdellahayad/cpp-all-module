#ifndef BEREAUCRAT_HPP
#define BEREAUCRAT_HPP


#include <string>
#include <exception>
#include <iostream>

class Bureaucrat
{ 
    private:
        const std::string name;
        int grade;
    public:
        Bureaucrat(const std::string& name, int grade);
        Bureaucrat(const Bureaucrat& copy);
        Bureaucrat& operator=(const Bureaucrat& other);
        ~Bureaucrat();

        const std::string& getName() const;
        int  getGrade() const;

        void incrementGrade();
        void decrementGrade();

        class GradeTooHighException : public std::exception
        {
            public:
                const char *what() const throw();
        };

        class GradeTooLowException : public std::exception
        {
            public:
                const char *what() const throw();
        };

        
};

std::ostream& operator<<(std::ostream& out, const  Bureaucrat &b);



#endif