#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int MAX_BRAND = 2147483647;

void printInput(const vector<int>& brands) {
    println((int)brands.size());
    for (int i = 0; i < (int)brands.size(); ++i) {
        if (i > 0) {
            if (i % 20 == 0) {
                printf("\n");
            } else {
                printf(" ");
            }
        }
        printf("%d", brands[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 80);
    vector<int> brands;

    if (mode == 0) {
        int start = rnd.next(1, 2000000000 - n);
        int step = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            brands.push_back(start + i * step);
        }
    } else if (mode == 1) {
        int step = rnd.next(1, 20);
        int start = rnd.next(1 + (n - 1) * step, 2000000000);
        for (int i = 0; i < n; ++i) {
            brands.push_back(start - i * step);
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            brands.push_back(i);
        }
        shuffle(brands.begin(), brands.end());
    } else if (mode == 3) {
        int blockSize = rnd.next(2, 8);
        int base = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            int block = i / blockSize;
            int offset = i % blockSize;
            brands.push_back(base + block * blockSize + (blockSize - offset));
        }
    } else if (mode == 4) {
        int low = 1;
        int high = n;
        while ((int)brands.size() < n) {
            brands.push_back(high--);
            if ((int)brands.size() < n) {
                brands.push_back(low++);
            }
        }
    } else {
        int gap = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            brands.push_back(MAX_BRAND - i * gap);
        }
        if (rnd.next(0, 1) == 1) {
            reverse(brands.begin(), brands.end());
        }
    }

    set<int> seen;
    for (int brand : brands) {
        ensure(1 <= brand && brand <= MAX_BRAND);
        ensure(seen.insert(brand).second);
    }

    printInput(brands);
    return 0;
}
