#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeNumber(int D, int mode) {
    string s(D, '0');

    if (mode == 0) {
        s[0] = char('1' + rnd.next(9));
        return s;
    }

    if (mode == 1) {
        s[0] = '1';
        for (int i = 1; i < D; ++i) s[i] = rnd.next(3) == 0 ? '1' : '0';
        return s;
    }

    if (mode == 2) {
        s[0] = char('2' + rnd.next(8));
        for (int i = 1; i < D; ++i) s[i] = rnd.next(4) == 0 ? char('2' + rnd.next(8)) : '0';
        return s;
    }

    if (mode == 3) {
        for (int i = 0; i < D; ++i) s[i] = char('1' + rnd.next(9));
        return s;
    }

    s[0] = char('1' + rnd.next(9));
    for (int i = 1; i < D; ++i) s[i] = char('0' + rnd.next(10));
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 12);
    vector<int> D(T), K(T);
    int remainingD = rnd.next(T, 80);
    int remainingK = rnd.next(T, 80);

    for (int i = 0; i < T; ++i) {
        int left = T - i - 1;
        int maxD = remainingD - left;
        int maxK = remainingK - left;

        D[i] = rnd.next(1, min(25, maxD));
        K[i] = rnd.next(1, min(25, maxK));

        remainingD -= D[i];
        remainingK -= K[i];
    }

    println(T);
    for (int i = 0; i < T; ++i) {
        println(D[i], K[i]);
        println(makeNumber(D[i], rnd.next(5)));
    }

    return 0;
}
