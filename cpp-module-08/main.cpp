#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <map>



int main()
{
    std::list<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    l.push_back(40);
    l.push_back(50);

    std::list<int>::iterator it = l.begin();
    std::list<int>::iterator ite = l.end();

    while (it != ite)
    {
        std::cout << *it << std::endl;
        it++;
    }

    std::vector<std::string> v;
    v.push_back("yassine");
    v.push_back("abdellah");
    v.push_back("mounaim");
    v.push_back("mohamed");
    v.push_back("rida");

    std::vector<std::string>::iterator it2 = v.begin();
    std::vector<std::string>::iterator ite2 = v.end();

    while (it2 != ite2)
    {
        std::cout << *ite << std::endl;
        it2++;
    }

    std::stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    while (!s.empty())
    {
        std::cout << s.top() << std::endl;
        s.pop();
    }

    std::map<std::string, std::string> m;
    m["abdellah"] = "2000";
    m["yassine"] = "2006";
    m["nouh"] = "1997";

    std::map<std::string, std::string>::iterator mit = m.begin();
    std::map<std::string, std::string>::iterator mite = m.end();

    while (mit != mite)
    {
        std::cout << mit->first << " : " << mit->second << std::endl;
        mit++;
    }

}