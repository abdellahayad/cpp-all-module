#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

int main()
{
    int count = 0;
    std::ifstream file("data.txt");

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }

    int start = 50;
    int value = 0;
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream aa(line);
        char c;
        aa >> c;
        int value;
        aa >> value;
        for (int i = 0; i < value; i++)
        {
            if (c == 'L')
                start = (start + 1) % 100;
            else
                start = (start - 1) % 100;
            if (start == 0)
                count++;
        }
    }

    file.close();
    std::cout << count << std::endl;
}