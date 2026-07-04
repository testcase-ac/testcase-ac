#include "testlib.h"

#include <vector>
using namespace std;

vector<int> repeatedBits(int n, int bit) {
    return vector<int>(n, bit);
}

vector<int> alternatingBits(int n, int first) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = (first + i) % 2;
    return a;
}

vector<int> blockBits(int n) {
    vector<int> a;
    a.reserve(n);

    int firstZeros = rnd.next(0, n);
    int middleOnes = rnd.next(0, n - firstZeros);
    int lastZeros = n - firstZeros - middleOnes;

    for (int i = 0; i < firstZeros; ++i) a.push_back(0);
    for (int i = 0; i < middleOnes; ++i) a.push_back(1);
    for (int i = 0; i < lastZeros; ++i) a.push_back(0);
    return a;
}

vector<int> biasedRandomBits(int n) {
    int threshold = rnd.next(1, 9);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = rnd.next(0, 9) < threshold ? 1 : 0;
    return a;
}

vector<int> randomBits(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = rnd.next(0, 1);
    return a;
}

vector<int> makeSequence(int n, int mode) {
    if (mode == 0) return repeatedBits(n, 0);
    if (mode == 1) return repeatedBits(n, 1);
    if (mode == 2) return alternatingBits(n, rnd.next(0, 1));
    if (mode == 3) return blockBits(n);
    if (mode == 4) return biasedRandomBits(n);
    return randomBits(n);
}

int compactLength() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return 1;
    if (mode == 1) return rnd.next(2, 6);
    if (mode == 2) return rnd.next(7, 20);
    if (mode == 3) return rnd.next(21, 60);
    if (mode == 4) return rnd.next(61, 120);
    return rnd.next(121, 200);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = compactLength();
    int m = compactLength();

    if (rnd.next(0, 4) == 0) {
        if (rnd.next(0, 1)) n = 1;
        else m = 1;
    }

    int modeA = rnd.next(0, 5);
    int modeB = rnd.next(0, 5);
    if (rnd.next(0, 3) == 0) modeB = modeA;

    vector<int> a = makeSequence(n, modeA);
    vector<int> b = makeSequence(m, modeB);

    println(n, m);
    println(a);
    println(b);

    return 0;
}
