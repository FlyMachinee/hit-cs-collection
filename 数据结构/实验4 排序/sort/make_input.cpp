#include "./src/sort.hpp"

using namespace std;

int main() {
    int scale = 1;

    for (int i = 1; i <= 5; ++i) {
        scale *= 10;

        string title = "./inputs/input_" + to_string(scale) + '_';
        string suffix = ".txt";
        default_random_engine e;
        e.seed(time(0));
        for (int j = 0; j < 10; ++j)
            My::make_int_to_file(title + to_string(j) + suffix, scale, e);
    }
    
    return 0;
}