#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int mode = rnd.next(1, 3);

    if (mode == 1) {
        // Prefer some hand-picked interesting values
        vector<int> special = {5, 6, 7, 8, 9, 10, 20, 30, 35, 39, 40};
        n = rnd.any(special);
    } else if (mode == 2) {
        // Uniform random in full range
        n = rnd.next(5, 40);
    } else {
        // Strong bias to boundaries
        n = (rnd.next(0, 1) == 0 ? 5 : 40);
    }

    println(n);
    return 0;
}
