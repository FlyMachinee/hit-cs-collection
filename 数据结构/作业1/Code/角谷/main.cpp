#include <iostream>
#include <array>
using namespace std;
int main()
{
    int max_len = 0, max_cnt = 0;
    int arr[100] = {0};
    for (int i = 1; i <= 100; i++){
        int m = i, len = 1;
        cout << "-> " << m << ' ';
        while (m != 1){
            if (m % 2 == 0){
                cout << (m /= 2) << ' ';
                len++;
            }else{
                cout << (m = 3 * m + 1) << ' ';
                len++;
            }
        }
        if (len == max_len){
            arr[max_cnt++] = i;
        }else if (len > max_len){
            max_cnt = 0;
            max_len = len;
            arr[max_cnt++] = i;
        }
        cout << endl;
    }
    cout << "max_len: " << max_len << endl;
    cout << "max_index: ";
    for (int i = 0; i < max_cnt; i++)
        cout << arr[i] << ' ';
    return 0;
}