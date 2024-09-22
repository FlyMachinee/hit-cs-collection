#include "Stack.hpp"
#include "Queue.hpp"

#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
    Stack<int> st;

    st.push(5);
    st.push(6);
    st.push(7);

    cout << st.top() << endl;

    st.pop();

    cout << st.top() << endl;

    Queue<int> q;
    q.push(5);
    q.push(8);

    cout << q.front() << endl;
    q.pop();
    cout << q.front() << endl;

    return 0;
}