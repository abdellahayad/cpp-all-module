#include <iostream>




class shallow
{
    private:
    public:
        int *node;
        shallow(int value) 
        {
            node = new int(value);
        }

        shallow(const shallow& o)
        {
            node = new int(*o.node);
        }

        shallow& operator=(const shallow& o)
        {
            node = new int(*o.node);
            return *this;
        }


        ~shallow()
        {
            delete node;
        }

};





int main()
{
    shallow a(30);
    shallow b(70);
    b = a;
    *b.node = 90;
    std::cout << *a.node << std::endl;
    std::cout << *b.node << std::endl;
}