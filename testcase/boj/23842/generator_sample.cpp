#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> impossibleLow = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> compact = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    vector<int> typical = {21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
    vector<int> upper = {31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.any(impossibleLow);
    } else if (mode == 1) {
        n = rnd.any(compact);
    } else if (mode == 2) {
        n = rnd.any(typical);
    } else if (mode == 3) {
        n = rnd.any(upper);
    } else {
        n = rnd.next(1, 50);
    }

    println(n);
    return 0;
}
