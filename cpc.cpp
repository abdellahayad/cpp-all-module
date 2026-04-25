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
// =================================================
if (v.size() <= 1)
    {
        std::cout << "the base case\n";
        return v;
    }

    std::vector<std::pair<int, int> > pairs;
    int leftover = -1;
    bool hasLeft = (v.size() % 2 != 0);
    for (size_t i = 0; i < v.size() - (hasLeft ? 1 : 0); i += 2)
    {
        if (v[i] > v[i + 1])
            pairs.push_back(std::make_pair(v[i], v[i + 1]));
        else
            pairs.push_back(std::make_pair(v[i + 1], v[i]));
    }
    if (hasLeft)
        leftover = v.back();

    std::vector<int> winners;
    for (size_t i = 0; i < pairs.size(); i++)
        winners.push_back(pairs[i].first);
    std::vector<int> mainChain = sortVector(winners);


    std::vector<int> pend;
    for (size_t i = 0; i < mainChain.size(); i++)
    {
        for (size_t j = 0; j < pairs.size(); j++)
        {
            if (mainChain[i] == pairs[j].first)
            {
                pend.push_back(pairs[j].second);
                break;
            }
        }
    }

    std::vector<int> result = mainChain;
    
    result.insert(result.begin(), pend[0]); 
    std::vector<int> jac = generateJacobsthal(pend.size());
    std::vector<bool> inserted(pend.size(), false);
    inserted[0] = true;

    for (size_t i = 0; i < jac.size(); i++)
    {
        int target = std::min(jac[i], (int)pend.size());
        for (int j = target - 1; j >= 0; j--)
        {
            if (!inserted[j])
            {
                result.insert(std::lower_bound(result.begin(), result.end(), pend[j]), pend[j]);
                inserted[j] = true;
            }
        }
        
    }
    if (hasLeft)
        result.insert(std::lower_bound(result.begin(), result.end(), leftover), leftover);
    return result;