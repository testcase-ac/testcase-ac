#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a scenario to cover edge and typical cases:
    // 0: all equal, 1: two equal (largest), 2: two equal (smallest), 3: all distinct
    int scenario = rnd.next(0, 3);
    int a, b, c;

    if (scenario == 0) {
        // All three are the same
        int x = rnd.next(1, 100);
        a = b = c = x;
    } else if (scenario == 1) {
        // Two equal values that are the largest
        int x = rnd.next(1, 100);
        int y = rnd.next(1, x);
        a = b = x;
        c = y;
    } else if (scenario == 2) {
        // Two equal values that are the smallest
        int x = rnd.next(1, 100);
        int y = rnd.next(x, 100);
        a = b = x;
        c = y;
    } else {
        // All three are distinct
        do {
            a = rnd.next(1, 100);
            b = rnd.next(1, 100);
            c = rnd.next(1, 100);
        } while (a == b || b == c || a == c);
    }

    // Shuffle order so positions vary
    vector<int> v = {a, b, c};
    shuffle(v.begin(), v.end());

    // Output the three numbers
    println(v);

    return 0;
}
