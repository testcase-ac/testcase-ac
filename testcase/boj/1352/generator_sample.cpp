#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> values;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        values = {1, 2, 3, 5, 6, 7};
    } else if (mode == 1) {
        values = {8, 9, 10, 11, 12, 13, 14, 15};
    } else if (mode == 2) {
        values = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
    } else if (mode == 3) {
        values = {26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};
    } else if (mode == 4) {
        values = {37, 38, 39, 40, 45, 50, 55, 60, 65, 70};
    } else {
        values = {75, 80, 85, 90, 95, 96, 97, 98, 99, 100};
    }

    println(rnd.any(values));
    return 0;
}
