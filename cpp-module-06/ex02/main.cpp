#include "base.hpp"


int main()
{
    Base *obj = generate();

    std::cout << "identify by ptr" << std::endl;
    identify(obj);
    std::cout << "----------------" << std::endl;
    std::cout << "identify by ref" << std::endl;
    identify(*obj);

    delete obj;
    return 0;
}
