#include <iostream>




class parent
{
    protected:
        std::string value;
        int *num;
    public:
        parent() : value("default") {
            num = new int(0);
        }
        parent(int x, std::string str) : value(str) {
            num = new int(x);
        }
        virtual void print() const
        {
            std::cout << "parent => "  << value <<  " " << *num << std::endl;   

        }
        virtual ~parent(){
            delete num;
        }
};


class child : public parent
{
    public:
        child() {value = "hello";}
        void print() const
        {
            std::cout << "child => " << value << std::endl;
        }
        ~child()
        {

        }
        
};



int main()
{
    parent p;
    child c;

    p.print();
    c.print();
  
    parent *ptr = new child;
    parent *ptr1 = new parent(10, "hello");
    ptr->print();
    ptr1->print();

    delete ptr;
    delete ptr1;
}