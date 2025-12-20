#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v;

    v.push_back(10);
    v.push_back(100);
    v.push_back(1000);
    v.push_back(10000);

    // std::cout << v.at(1) + 10 << std::endl;
    // std::cout << v.size() << std::endl;
    // std::cout <<  v.back() << std::endl;

    std::vector<int> v2(2, 5);

      std::cout << v2.at(1)<< std::endl;
      std::cout << v2.at(0)<< std::endl;
    std::cout << v2.size() << std::endl;
    std::cout <<  v2.back() << std::endl;

}