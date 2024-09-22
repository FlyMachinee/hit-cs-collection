#include <iostream>
#include <stack>
#include <time.h>

int step = 0;

typedef struct{
    int n;
    char from;
    char to;
    char by;
    bool can_solve;
}QUESTION;

void Hanoi(int n, char from, char to, char by)
{
    if (n == 1){
        //std::cout << "step " << ++step << ", plate " << n << ": " << from << "->" << to << std::endl;
    }else{
        Hanoi(n - 1, from, by, to);
        //std::cout << "step " << ++step << ", plate " << n << ": " << from << "->" << to << std::endl;
        Hanoi(n - 1, by, to, from);
    }
}

int main(int argc, char** argv)
{
    int n = atoi(argv[1]);
    std::stack<QUESTION> st;
    clock_t a, b;

    a = clock();
    QUESTION temp = {n, 'A', 'C', 'B', false};
    st.push(temp);
    while (!st.empty()){
        temp = st.top();
        st.pop();
        if (temp.n == 1 || temp.can_solve){
            //std::cout << "step " << ++step << ", plate " << temp.n << ": " << temp.from << "->" << temp.to << std::endl; 
        }else{
            st.push({temp.n - 1, temp.from, temp.by, temp.to, false});
            st.push({temp.n, temp.from, temp.to, temp.by, true});
            st.push({temp.n - 1, temp.by, temp.to, temp.from, false});
        }
    }
    b = clock();
    std::cout << "Non-recursion hanoi: " << (b - a) / (double)CLOCKS_PER_SEC << " seconds" << std::endl;

    step = 0;
    a = clock();
    Hanoi(n, 'A', 'C', 'B');
    b = clock();
    std::cout << "Recursion hanoi: " << (b - a) / (double)CLOCKS_PER_SEC << " seconds" << std::endl;

    return 0;
}