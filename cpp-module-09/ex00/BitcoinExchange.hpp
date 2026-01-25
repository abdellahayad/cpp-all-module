#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP



#include <map>
#include <iostream>


class BitcoinExchange
{
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& copy);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        void processFile(const std::string& fileName);
    private:
        std::map<std::string, double> rates;
        void loadData();
        bool isValidDate(const std::string& date) const;
        bool isValideValue(const std::string& value) const;
        double getRateForDate(const std::string& date) const;

};





#endif