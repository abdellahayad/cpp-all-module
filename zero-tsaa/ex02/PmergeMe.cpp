#include "PmergeMe.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>
#include <climits>
#include <cctype>

PmergeMe::PmergeMe()
    : _vectorTimeUs(0.0), _dequeTimeUs(0.0)
{
}

PmergeMe::PmergeMe(const PmergeMe& other)
    : _input(other._input),
      _vectorData(other._vectorData),
      _dequeData(other._dequeData),
      _vectorTimeUs(other._vectorTimeUs),
      _dequeTimeUs(other._dequeTimeUs)
{
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        _input = other._input;
        _vectorData = other._vectorData;
        _dequeData = other._dequeData;
        _vectorTimeUs = other._vectorTimeUs;
        _dequeTimeUs = other._dequeTimeUs;
    }
    return (*this);
}

PmergeMe::~PmergeMe()
{
}

bool PmergeMe::isPositiveInteger(const std::string& token) const
{
    if (token.empty())
        return false;

    for (size_t i = 0; i < token.size(); ++i)
    {
        if (!std::isdigit(static_cast<unsigned char>(token[i])))
            return false;
    }

    char* end = NULL;
    long value = std::strtol(token.c_str(), &end, 10);
    if (*end != '\0')
        return false;

    if (value <= 0 || value > INT_MAX)
        return false;

    return true;
}

void PmergeMe::parseInput(int argc, char** argv)
{
    if (argc < 2)
        throw std::runtime_error("Error");

    _input.clear();

    for (int i = 1; i < argc; ++i)
    {
        std::string token(argv[i]);

        if (!isPositiveInteger(token))
            throw std::runtime_error("Error");

        char* end = NULL;
        long value = std::strtol(token.c_str(), &end, 10);
        (void)end;
        _input.push_back(static_cast<int>(value));
    }

    _vectorData.assign(_input.begin(), _input.end());
    _dequeData.assign(_input.begin(), _input.end());
}

void PmergeMe::sortVector()
{
    clock_t start = std::clock();
    mergeInsertSort(_vectorData);
    clock_t end = std::clock();

    _vectorTimeUs = static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;
}

void PmergeMe::sortDeque()
{
    clock_t start = std::clock();
    mergeInsertSort(_dequeData);
    clock_t end = std::clock();

    _dequeTimeUs = static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;
}

void PmergeMe::process()
{
    sortVector();
    sortDeque();
}

std::string PmergeMe::containerToString(const std::vector<int>& container) const
{
    std::ostringstream output;

    for (size_t i = 0; i < container.size(); ++i)
    {
        output << container[i];
        if (i + 1 < container.size())
            output << " ";
    }

    return output.str();
}

void PmergeMe::printResults() const
{
    std::cout << "Before: " << containerToString(_input) << std::endl;
    std::cout << "After:  " << containerToString(_vectorData) << std::endl;

    std::cout << "Time to process a range of "
              << _input.size()
              << " elements with std::vector<int> : "
              << _vectorTimeUs
              << " us"
              << std::endl;

    std::cout << "Time to process a range of "
              << _input.size()
              << " elements with std::deque<int> : "
              << _dequeTimeUs
              << " us"
              << std::endl;
}
