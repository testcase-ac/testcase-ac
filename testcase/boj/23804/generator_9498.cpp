#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    // Choose N with diverse size buckets to get varied test cases
    int bucket = rnd.next(1, 8);
    if (bucket == 1) {
        // minimum
        N = 1;
    } else if (bucket == 2) {
        // very small
        N = rnd.next(2, 4);
    } else if (bucket == 3) {
        // small
        N = rnd.next(5, 10);
    } else if (bucket == 4) {
        // medium-small
        N = rnd.next(11, 20);
    } else if (bucket == 5) {
        // medium
        N = rnd.next(21, 50);
    } else if (bucket == 6) {
        // medium-large
        N = rnd.next(51, 80);
    } else if (bucket == 7) {
        // large but not max
        N = rnd.next(81, 99);
    } else {
        // maximum
        N = 100;
    }

    println(N);
    return 0;
}
