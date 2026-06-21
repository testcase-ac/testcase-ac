#include "testlib.h"
#include <vector>
using namespace std;

vector<int> makeBits(int len, int mode) {
    vector<int> bits(len);
    if (mode == 0) {
        int value = rnd.next(0, 1);
        for (int i = 0; i < len; ++i) bits[i] = value;
    } else if (mode == 1) {
        for (int i = 0; i < len; ++i) bits[i] = i % 2;
    } else if (mode == 2) {
        for (int i = 0; i < len; ++i) bits[i] = (i + 1) % 2;
    } else if (mode == 3) {
        int split = rnd.next(0, len);
        int first = rnd.next(0, 1);
        for (int i = 0; i < len; ++i) bits[i] = (i < split ? first : 1 - first);
    } else {
        int p = rnd.next(10, 90);
        for (int i = 0; i < len; ++i) bits[i] = rnd.next(1, 100) <= p;
    }
    return bits;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m;
    if (mode == 0) {
        n = rnd.next(1, 6);
        m = rnd.next(1, 6);
    } else if (mode == 1) {
        n = 1;
        m = rnd.next(1, 40);
    } else if (mode == 2) {
        n = rnd.next(1, 40);
        m = 1;
    } else if (mode == 3) {
        vector<int> sizes = {2, 3, 4, 5, 8, 9, 16, 17, 32};
        n = rnd.any(sizes);
        m = rnd.any(sizes);
    } else if (mode == 4) {
        n = rnd.next(30, 120);
        m = rnd.next(30, 120);
    } else {
        n = rnd.next(99950, 100000);
        m = rnd.next(1, 20);
        if (rnd.next(0, 1)) swap(n, m);
    }

    vector<int> left = makeBits(n, rnd.next(0, 4));
    vector<int> top = makeBits(m, rnd.next(0, 4));

    println(n, m);
    println(left);
    println(top);
    return 0;
}
