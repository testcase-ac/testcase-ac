#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int fromBits(const vector<int>& bits) {
    int value = 0;
    for (int bit : bits) value |= 1 << bit;
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int scoreA = 0;
    int scoreB = 0;

    if (mode == 0) {
        scoreA = rnd.next(0, 1023);
        scoreB = scoreA;
    } else if (mode == 1) {
        scoreA = rnd.any(vector<int>{0, 1023});
        scoreB = rnd.next(0, 1023);
    } else if (mode == 2) {
        scoreA = rnd.next(0, 1023);
        scoreB = 1023 - scoreA;
    } else if (mode == 3) {
        int common = rnd.next(0, 1023);
        int diff = 1 << rnd.next(0, 9);
        scoreA = common;
        scoreB = common ^ diff;
    } else if (mode == 4) {
        vector<int> bits;
        for (int bit = 0; bit < 10; ++bit) bits.push_back(bit);
        shuffle(bits.begin(), bits.end());

        int countA = rnd.next(0, 10);
        int countB = rnd.next(0, 10);
        scoreA = fromBits(vector<int>(bits.begin(), bits.begin() + countA));
        shuffle(bits.begin(), bits.end());
        scoreB = fromBits(vector<int>(bits.begin(), bits.begin() + countB));
    } else if (mode == 5) {
        int lowMask = (1 << rnd.next(1, 5)) - 1;
        int highMask = 1023 ^ ((1 << rnd.next(5, 10)) - 1);
        scoreA = rnd.next(0, lowMask);
        scoreB = highMask | rnd.next(0, 1023 ^ highMask);
    } else {
        scoreA = rnd.next(0, 1023);
        scoreB = rnd.next(0, 1023);
    }

    println(scoreA, scoreB);
    return 0;
}
