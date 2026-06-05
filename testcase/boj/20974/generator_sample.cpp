#include "testlib.h"

#include <vector>

using namespace std;

int nextOdd() {
    return rnd.next(0, 49) * 2 + 1;
}

int nextEven() {
    return rnd.next(1, 50) * 2;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 30);
    int odd = 0;
    int even = 0;

    if (mode == 0) {
        odd = n;
    } else if (mode == 1) {
        even = n;
    } else if (mode == 2) {
        odd = rnd.next(1, n);
        even = n - odd;
    } else if (mode == 3) {
        odd = rnd.next(2, n);
        even = rnd.next(0, odd);
        n = odd + even;
    } else if (mode == 4) {
        even = rnd.next(0, n - 1);
        odd = n - even;
        if (odd < 2 * even + 1) {
            odd = min(n, 2 * even + 1);
            even = n - odd;
        }
    } else {
        n = rnd.next(2, 100);
        odd = rnd.next(0, n);
        even = n - odd;
    }

    vector<int> breeds;
    for (int i = 0; i < odd; ++i) {
        breeds.push_back(nextOdd());
    }
    for (int i = 0; i < even; ++i) {
        breeds.push_back(nextEven());
    }
    shuffle(breeds.begin(), breeds.end());

    println(n);
    println(breeds);

    return 0;
}
