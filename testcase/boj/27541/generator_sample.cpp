#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 8);
    } else if (mode == 2) {
        n = rnd.next(9, 30);
    } else if (mode == 3) {
        n = rnd.next(31, 100);
    } else {
        n = rnd.next(2, 100);
    }

    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (mode == 1) {
        alphabet = "JOG";
    } else if (mode == 2) {
        alphabet = "ABCG";
    } else if (mode == 3) {
        alphabet = "GXYZ";
    }

    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += rnd.any(alphabet);
    }

    if (mode % 2 == 0) {
        s.back() = 'G';
    } else if (s.back() == 'G') {
        s.back() = rnd.any(string("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
        if (s.back() == 'G') {
            s.back() = 'A';
        }
    }

    println(n);
    println(s);

    return 0;
}
