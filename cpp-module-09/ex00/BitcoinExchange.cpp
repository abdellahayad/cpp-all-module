#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    loadData();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) : rates(copy.rates) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
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
        return;
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
            double rate = strtod(ratestr.c_str(), NULL);
            rates[date] = rate;
            // std::cout << date << "--";
            // std::cout << rates[date] << std::endl;
        }
    }
    file.close();
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }

    int year = strtol(date.substr(0, 4).c_str(), NULL, 10);
    int month = strtol(date.substr(5, 2).c_str(), NULL, 10);
    int day = strtol(date.substr(8, 2).c_str(), NULL, 10);

    // std::cout << year << " - " << month << " - " << day << std::endl;

    if (year < 2009 || year > 2024)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    if (month == 2)
    {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        {
            if (day > 29)
                return false;
        }
        else
        {
            if (day > 28)
                return false;
        }
    }

    return true;
}

bool BitcoinExchange::isValideValue(const std::string &value) const
{
    char *end;
    double number = strtod(value.c_str(), &end);

    if (*end != '\0')
        return false;

    if (number < 0 || number > 100)
        return false;

    return true;
}

double BitcoinExchange::getRate(const std::string &date) const
{
    std::map<std::string, double>::const_iterator it;

    it = rates.find(date);

    if (it != rates.end())
        return it->second;

    it = rates.lower_bound(date);

    if (it == rates.begin())
        return (-1);

    --it;

    return it->second;
}

void BitcoinExchange::processFile(const std::string &fileName)
{
    std::ifstream file(fileName);

    if (!file.is_open())
    {
        std::cerr << "Error: file could not open." << std::endl;
        return ;
    }

    std::string line;
    std::getline(file, line);

    while(std::getline(file, line))
    {
        size_t pipe = line.find(" | ");
        if (pipe == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue ;
        }

        std::string date = line.substr(0, pipe);
        std::string value = line.substr(pipe + 3);
        
        date.erase(0, date.find_first_not_of(" \t"));
        date.erase(date.find_last_not_of(" \t") + 1);

        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);\

        std::cout << value << " <====> " << date << std::endl;

        if (!isValidDate(date))
        {
            std::cerr << "Error: invalid value." << std::endl;
            continue ;
        }
        if (!isValideValue(value))
        {
            
        }

    }
}