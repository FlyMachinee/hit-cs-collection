#include <iostream>
#include <stack>

typedef struct{
    int n;
    char from;
    char to;
    char by;
    bool can_solve;
}QUESTION;

int main()
{
    int n, step = 0;
    std::cin >> n;
    std::stack<QUESTION> st;
    QUESTION temp = {n, 'A', 'C', 'B', false};
    st.push(temp);
    size_t max_size = 1;
    while (!st.empty()){
        temp = st.top();
        st.pop();
        if (temp.n == 1 || temp.can_solve){
            std::cout << "step " << ++step << ", plate " << temp.n << ": " << temp.from << "->" << temp.to << std::endl; 
        }else{
            st.push({temp.n - 1, temp.from, temp.by, temp.to, false});
            st.push({temp.n, temp.from, temp.to, temp.by, true});
            st.push({temp.n - 1, temp.by, temp.to, temp.from, false});
            max_size = std::max(max_size, st.size());
        }
    }
    std::cout << "max size: " << max_size;
    return 0;
}