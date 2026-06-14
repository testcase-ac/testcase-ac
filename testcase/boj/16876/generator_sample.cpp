#include "testlib.h"

#include <cstdio>
#include <string>
#include <vector>
using namespace std;

string fourDigits(int value) {
    char buffer[5];
    snprintf(buffer, sizeof(buffer), "%04d", value);
    return string(buffer);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;

    if (mode == 0) {
        n = rnd.next(0, 99);
    } else if (mode == 1) {
        int digit = rnd.next(0, 9);
        n = digit * 1111;
    } else if (mode == 2) {
        n = rnd.any(vector<int>{9, 90, 99, 900, 909, 990, 999});
    } else if (mode == 3) {
        n = rnd.next(9000, 9999);
    } else if (mode == 4) {
        int a = rnd.next(0, 9);
        int b = rnd.next(0, 9);
        n = 1000 * a + 100 * b + 10 * a + b;
    } else if (mode == 5) {
        n = rnd.next(0, 9999);
    } else {
        n = rnd.any(vector<int>{0, 1, 1234, 3333, 5566, 9999});
    }

    int turnMode = rnd.next(0, 4);
    int m;
    if (turnMode == 0) {
        m = 0;
    } else if (turnMode == 1) {
        m = rnd.next(1, 9);
    } else if (turnMode == 2) {
        m = rnd.next(10, 40);
    } else if (turnMode == 3) {
        m = rnd.next(80, 100);
    } else {
        m = rnd.next(0, 100);
    }

    println(fourDigits(n), m);
    return 0;
}
