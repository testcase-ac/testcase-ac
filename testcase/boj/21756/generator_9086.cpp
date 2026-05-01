#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    int choice = rnd.next(1, 6);

    if (choice == 1) {
        // Very small N
        N = rnd.next(1, 5);
    } else if (choice == 2) {
        // Completely random in full range
        N = rnd.next(1, 100);
    } else if (choice == 3) {
        // Powers of two
        vector<int> v = {1, 2, 4, 8, 16, 32, 64};
        N = rnd.any(v);
    } else if (choice == 4) {
        // Just above powers of two
        vector<int> v = {3, 5, 9, 17, 33, 65};
        N = rnd.any(v);
    } else if (choice == 5) {
        // Just below powers of two
        vector<int> v = {3, 7, 15, 31, 63};
        N = rnd.any(v);
    } else {
        // Medium to large values, including near the maximum
        N = rnd.next(40, 100);
    }

    println(N);
    return 0;
}
