#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main()
{
    stack<int> st;
    st.push(10);
    st.push(20);
    st.push(30);
    st.push(40);

    cout << st.top() << endl;
    st.pop();
    st.pop();
    st.pop();
    cout << st.top() << endl;
    return 0;
}