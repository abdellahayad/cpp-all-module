#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange()
{
    loadData();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy) : rates(copy.rates) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
        rates = other.rates;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadData()
{
    std::ifstream file("data.csv");

    if (!file.is_open())
    {
        std::cerr << "Error: cannot open data.csv";
        return ;
    }

    std::string line;

    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::stringstream iss(line);
        std::string date;
        std::string ratestr;

        if (std::getline(iss, date, ',') && std::getline(iss, ratestr))
        {
            double  rate = strtod(ratestr.c_str(), NULL);
            rates[date] = rate;
            // std::cout << date << "--";
            // std::cout << rates[date] << std::endl;
        }
    }
    file.close();
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
            continue ;
        if (!std::isdigit(date[i]))
            return false;
    }

    
}