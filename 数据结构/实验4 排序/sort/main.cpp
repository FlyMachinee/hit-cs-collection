#define DEBUG 0

#include "./src/sort.hpp"
#include <chrono>

using namespace std;

int arr[100007];
int temp[100007];

#if DEBUG // DEBUG == 1

int main() {
    ifstream input_1("./inputs/input_100_0.txt");
    ifstream input_2("./inputs/input_100_1.txt");
    int n = 0;

    input_1 >> n;
    for (int i = 0; i < n; ++i)
        input_1 >> arr[i];

    auto start = chrono::system_clock::now();
    My::quick_sort(arr, 0, 99);
    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    double t1 = double(duration.count()) * chrono::microseconds::period::num / chrono::microseconds::period::den;

    cout << "sorted by quick_sort\n";
    for (int i = 0; i < n; ++i)
        cout << arr[i] << '\n';
    cout << "using time: " << t1 << " seconds" << endl;
    
    input_2 >> n;
    for (int i = 0; i < n; ++i)
        input_2 >> arr[i];

    start = chrono::system_clock::now();
    My::merge_sort(arr, 0, 99);
    end = chrono::system_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    double t2 = double(duration.count()) * chrono::microseconds::period::num / chrono::microseconds::period::den;

    cout << "sorted by merge_sort\n";
    for (int i = 0; i < n; ++i)
        cout << arr[i] << '\n';
    cout << "using time: " << t2 << " seconds" << endl;
}

#else // DEBUG == 0

int main(){
    int scale = 1;

    void (*fp[5]) (int*, int) = {
        My::selection_sort<int>, 
        My::insertion_sort<int>, 
        My::quick_sort<int>, 
        My::merge_sort<int>, 
        My::heap_sort<int>
    };

    string sort_type[5] = {
        "selection_sort",
        "insertion_sort",
        "quick_sort",
        "merge_sort",
        "heap_sort"
    };

    double total_time[5] = {0};
    string prefix = "./inputs/input_";
    string suffix = ".txt";

    for (int i = 1; i <= 5; ++i) { // for every scale
        scale *= 10;

        // clear
        for (int m = 0; m < 5; ++m)
            total_time[m] = 0; 

        for (int j = 0; j < 10; ++j) { // for every file in same scale
            string filename = prefix + to_string(scale) + '_' + to_string(j) + suffix;

            // read file
            ifstream input(filename);
            int n = 0;
            input >> n;
            for (int m = 0; m < n; ++m)
                input >> arr[m];

            for (int k = 0; k < 5; ++k) { // for every sort way
                memcpy(temp, arr, sizeof(int) * scale);
                auto start = chrono::system_clock::now();

                fp[k](temp, scale);

                auto end = chrono::system_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                total_time[k] += double(duration.count()) * chrono::microseconds::period::num / chrono::microseconds::period::den;
            }
        }

        cout << "In scale " << scale << '\n';
        for (int m = 0; m < 5; ++m) {
            cout << sort_type[m] << ": " << total_time[m] / 10 << " s\n";
        }
        cout << endl;
    }

    return 0;
}

#endif // DEBUG