#ifndef RPN_HPP
#define RPN_HPP



#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <algorithm>
#include <deque>


class RPN
{
    public: 
        RPN();
        RPN(const RPN& copy);
        RPN& operator=(const RPN& other);
        ~RPN();
        
        int calculate(const std::string& str);
    
        private:
            std::deque<double> stack;

            bool isNum(const std::string& num) const;
            bool isopr(const std::string& opr) const;

            double applyOperation(double a, double b, char opr);
};









#endif