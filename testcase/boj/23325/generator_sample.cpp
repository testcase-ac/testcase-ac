#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

string numberToken(int mode) {
    if (mode == 0) {
        return string(1, rnd.any(string("+-")));
    }
    if (mode == 1) {
        return rnd.next(0, 99) < 65 ? "+-" : string(1, rnd.any(string("+-")));
    }
    if (mode == 2) {
        return rnd.next(0, 99) < 80 ? "+" : "-";
    }
    return rnd.next(0, 99) < 80 ? "-" : "+-";
}

char operatorToken(int mode) {
    if (mode == 2) {
        return rnd.next(0, 99) < 70 ? '+' : '-';
    }
    if (mode == 3) {
        return rnd.next(0, 99) < 70 ? '-' : '+';
    }
    return rnd.any(string("+-"));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int terms;
    if (rnd.next(0, 99) < 85) {
        terms = rnd.next(1, 18);
    } else {
        terms = rnd.next(19, 80);
    }

    string s;
    for (int i = 0; i < terms; ++i) {
        s += numberToken(mode);
        if (i + 1 < terms) {
            s += operatorToken(mode);
        }
    }

    println(s);
    return 0;
}
