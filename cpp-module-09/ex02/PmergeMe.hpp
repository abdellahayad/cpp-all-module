#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <ctime>
#include <algorithm>

class PmergeMe
{
    public:
        PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        void parseInput(int argc, char** argv);
        void process();
        void printResults() const;

    private:
        std::vector<int> _input;
        std::vector<int> _vectorData;
        std::deque<int> _dequeData;

        double _vectorTimeUs;
        double _dequeTimeUs;

        bool isPositiveInteger(const std::string& token) const;

        template <typename Container>
        void mergeInsertSort(Container& container);

        template <typename Container>
        void binaryInsert(Container& sorted, typename Container::value_type value);

        void sortVector();
        void sortDeque();

        std::string containerToString(const std::vector<int>& container) const;
    };

template <typename Container>
void PmergeMe::binaryInsert(Container& sorted, typename Container::value_type value)
{
    typename Container::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), value);
    sorted.insert(pos, value);
}

template <typename Container>
void PmergeMe::mergeInsertSort(Container& container)
{
    if (container.size() <= 1)
        return;

    Container mainChain;
    Container pending;

    for (size_t index = 0; index + 1 < container.size(); index += 2)
    {
        typename Container::value_type first = container[index];
        typename Container::value_type second = container[index + 1];

        if (first < second)
        {
            mainChain.push_back(second);
            pending.push_back(first);
        }
        else
        {
            mainChain.push_back(first);
            pending.push_back(second);
        }
    }

    bool hasStraggler = (container.size() % 2 != 0);
    typename Container::value_type straggler = 0;
    if (hasStraggler)
        straggler = container[container.size() - 1];

    mergeInsertSort(mainChain);

    for (size_t index = 0; index < pending.size(); ++index)
        binaryInsert(mainChain, pending[index]);

    if (hasStraggler)
        binaryInsert(mainChain, straggler);

    container = mainChain;
}

#endif
