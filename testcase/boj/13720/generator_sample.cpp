#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> small = {1, 2, 3, 4, 5, 6, 7};
    vector<int> odd = {9, 11, 13, 15, 17, 19};
    vector<int> even = {8, 10, 12, 14, 16, 18, 20};
    vector<int> medium = {21, 25, 30, 37, 42, 50, 63};
    vector<int> large = {75, 88, 99, 100};

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.any(small);
    } else if (mode == 1) {
        n = rnd.any(odd);
    } else if (mode == 2) {
        n = rnd.any(even);
    } else if (mode == 3) {
        n = rnd.any(medium);
    } else if (mode == 4) {
        n = rnd.any(large);
    } else {
        n = rnd.next(1, 100);
    }

    println(n);
    return 0;
}
