#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

namespace {
const int MAX_A = (1 << 20) - 1;

int randomMask(int maxBits) {
    int bits = rnd.next(0, maxBits);
    int value = 0;
    vector<int> positions(20);
    for (int i = 0; i < 20; ++i) positions[i] = i;
    shuffle(positions.begin(), positions.end());
    for (int i = 0; i < bits; ++i) value |= 1 << positions[i];
    return value;
}

void printCase(int k, vector<int> a) {
    shuffle(a.begin(), a.end());
    println(static_cast<int>(a.size()), k);
    println(a);
}
}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);
    int k = rnd.next(1, n);
    vector<int> a;

    if (mode == 0) {
        a.resize(n);
        int limit = (1 << rnd.next(1, 20)) - 1;
        for (int& x : a) x = rnd.next(0, limit);
    } else if (mode == 1) {
        int base = randomMask(8);
        k = rnd.next(1, n);
        int carriers = rnd.next(k, n);
        for (int i = 0; i < carriers; ++i) a.push_back(base | randomMask(8));
        while (static_cast<int>(a.size()) < n) {
            int dropBit = rnd.next(0, 19);
            a.push_back(randomMask(12) & ~(1 << dropBit) & ~base);
        }
    } else if (mode == 2) {
        k = n;
        int common = randomMask(6);
        for (int i = 0; i < n; ++i) a.push_back(common | randomMask(10));
    } else if (mode == 3) {
        int value = rnd.next(0, MAX_A);
        a.assign(n, value);
        k = rnd.next(1, n);
    } else if (mode == 4) {
        n = rnd.next(3, 18);
        k = rnd.next(2, n);
        int target = rnd.next(0, MAX_A);
        for (int i = 0; i < k; ++i) a.push_back(target | randomMask(5));
        while (static_cast<int>(a.size()) < n) {
            int bit = rnd.next(0, 19);
            a.push_back((target & ~(1 << bit)) | randomMask(5));
        }
    } else {
        n = rnd.next(2, 18);
        k = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(MAX_A);
            } else {
                a.push_back(MAX_A ^ randomMask(10));
            }
        }
    }

    printCase(k, a);
    return 0;
}
