#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeParents(int n, int mode) {
    vector<int> parent(n + 1);
    for (int i = 2; i <= n; ++i) {
        if (mode == 0) {
            parent[i] = i - 1;
        } else if (mode == 1) {
            parent[i] = 1;
        } else if (mode == 2) {
            parent[i] = i / 2;
        } else if (mode == 3) {
            parent[i] = max(1, i - rnd.next(1, min(i - 1, 4)));
        } else {
            parent[i] = rnd.next(1, i - 1);
        }
    }
    return parent;
}

vector<int> makeFrequencies(int n, int mode) {
    vector<int> a(n + 1);
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    vector<int> powers = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512,
                          1024, 2048, 4096, 8192, 16384, 32768, 65536};
    vector<int> divisors = {1, 2, 3, 4, 5, 6, 10, 12, 15, 20, 25, 30,
                            50, 60, 75, 100, 150, 300, 600};

    for (int i = 1; i <= n; ++i) {
        if (mode == 0) {
            a[i] = 1;
        } else if (mode == 1) {
            int base = rnd.next(1, 12);
            a[i] = base * rnd.next(1, 8);
        } else if (mode == 2) {
            a[i] = rnd.any(divisors);
        } else if (mode == 3) {
            a[i] = rnd.any(powers);
        } else if (mode == 4) {
            a[i] = rnd.any(primes) * rnd.next(1, 9);
        } else {
            a[i] = rnd.next(99960, 100000);
        }
    }

    if (mode == 1 && n >= 4) {
        a[1] = 6;
        a[2] = 10;
        a[3] = 15;
        a[4] = 30;
    }

    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 9);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode <= 3) {
        n = rnd.next(2, 6);
    } else {
        n = rnd.next(7, 20);
    }

    int treeMode = rnd.next(0, 4);
    int freqMode = rnd.next(0, 5);

    vector<int> a = makeFrequencies(n, freqMode);
    vector<int> parent = makeParents(n, treeMode);

    println(n);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            printf(" ");
        }
        printf("%d", a[i]);
    }
    printf("\n");

    for (int i = 2; i <= n; ++i) {
        if (i > 2) {
            printf(" ");
        }
        printf("%d", parent[i]);
    }
    printf("\n");

    return 0;
}
