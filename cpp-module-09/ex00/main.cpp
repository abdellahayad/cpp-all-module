#include "BitcoinExchange.hpp"


int main(int ac, char **av)
{
    (void)av;
    if (ac != 2)
    {
        std::cerr << "Usage: ./btc <input_file>" << std::endl;
        return (1);
    }

    BitcoinExchange btc;
    
}
