#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(5);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode <= 2) {
        n = rnd.next(2, 12);
    } else {
        n = rnd.next(13, 40);
    }

    int q = rnd.next(1, min(45, n * (n + 1) / 2));
    vector<int> breeds(n);
    int breedMode = rnd.next(5);

    if (breedMode == 0) {
        int breed = rnd.next(1, 3);
        fill(breeds.begin(), breeds.end(), breed);
    } else if (breedMode == 1) {
        for (int i = 0; i < n; ++i) {
            breeds[i] = i % 3 + 1;
        }
    } else if (breedMode == 2) {
        int split1 = rnd.next(0, n);
        int split2 = rnd.next(split1, n);
        for (int i = 0; i < n; ++i) {
            breeds[i] = (i < split1 ? 1 : (i < split2 ? 2 : 3));
        }
    } else if (breedMode == 3) {
        int commonBreed = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            breeds[i] = rnd.next(100) < 75 ? commonBreed : rnd.next(1, 3);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            breeds[i] = rnd.next(1, 3);
        }
    }

    if (rnd.next(2)) {
        shuffle(breeds.begin(), breeds.end());
    }

    println(n, q);
    for (int breed : breeds) {
        println(breed);
    }

    for (int i = 0; i < q; ++i) {
        int queryMode = rnd.next(5);
        int a, b;
        if (queryMode == 0) {
            a = 1;
            b = n;
        } else if (queryMode == 1) {
            a = b = rnd.next(1, n);
        } else if (queryMode == 2) {
            a = rnd.next(1, n);
            b = min(n, a + rnd.next(0, min(4, n - a)));
        } else if (queryMode == 3) {
            b = rnd.next(1, n);
            a = max(1, b - rnd.next(0, min(4, b - 1)));
        } else {
            a = rnd.next(1, n);
            b = rnd.next(a, n);
        }
        println(a, b);
    }

    return 0;
}
