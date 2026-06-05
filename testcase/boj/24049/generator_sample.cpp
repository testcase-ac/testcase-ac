#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeBits(int len, int mode) {
    vector<int> bits(len);
    if (mode == 0) {
        fill(bits.begin(), bits.end(), 0);
    } else if (mode == 1) {
        fill(bits.begin(), bits.end(), 1);
    } else if (mode == 2) {
        int start = rnd.next(0, 1);
        for (int i = 0; i < len; ++i) bits[i] = (start + i) % 2;
    } else if (mode == 3) {
        int block = rnd.next(1, 6);
        int start = rnd.next(0, 1);
        for (int i = 0; i < len; ++i) bits[i] = (start + i / block) % 2;
    } else {
        int onesBias = rnd.next(1, 9);
        for (int i = 0; i < len; ++i) bits[i] = rnd.next(1, 10) <= onesBias;
    }
    return bits;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int shape = rnd.next(0, 5);
    int n;
    int m;
    if (shape == 0) {
        n = 1;
        m = rnd.next(1, 25);
    } else if (shape == 1) {
        n = rnd.next(1, 25);
        m = 1;
    } else if (shape == 2) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 8);
    } else if (shape == 3) {
        n = rnd.next(9, 35);
        m = rnd.next(9, 35);
    } else if (shape == 4) {
        n = rnd.next(1, 40);
        m = rnd.next(200, 1000);
    } else {
        n = rnd.next(200, 1000);
        m = rnd.next(1, 40);
    }

    vector<int> left = makeBits(n, rnd.next(0, 4));
    vector<int> top = makeBits(m, rnd.next(0, 4));

    println(n, m);
    println(left);
    println(top);
    return 0;
}
