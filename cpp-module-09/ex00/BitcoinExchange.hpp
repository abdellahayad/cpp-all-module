#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP


#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>




class BitcoinExchange
{
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& copy);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        void processFile(const std::string& fileName);

        // private:
          
            std::map<std::string, double> rates;
            void loadData();
            bool isValidDate(const std::string& date) const;
            bool isValideValue(const std::string& value) const;
            double getRate(const std::string& date) const;

};











#endif