#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string alphabet = "joiJOI";
    int mode = rnd.next(0, 5);
    int n;
    int k;
    string t;

    if (mode == 0) {
        n = 1;
        k = 1;
        t += rnd.any(alphabet);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        k = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        k = n;
    } else if (mode == 3) {
        n = rnd.next(3, 30);
        k = rnd.next(2, n - 1);
    } else if (mode == 4) {
        n = 100;
        k = rnd.next(1, n);
    } else {
        n = rnd.next(1, 100);
        k = rnd.next(1, n);
    }

    if (t.empty()) {
        int pattern = rnd.next(0, 4);
        for (int i = 0; i < n; ++i) {
            if (pattern == 0) {
                t += alphabet[i % (int)alphabet.size()];
            } else if (pattern == 1) {
                t += alphabet[(i + k - 1) % (int)alphabet.size()];
            } else if (pattern == 2) {
                t += rnd.next(0, 1) ? "JOI"[rnd.next(0, 2)] : "joi"[rnd.next(0, 2)];
            } else if (pattern == 3) {
                char base = "joi"[rnd.next(0, 2)];
                if ((i + k) % 2 == 0) base = char(base - 'a' + 'A');
                t += base;
            } else {
                t += rnd.any(alphabet);
            }
        }
    }

    println(n, k);
    println(t);
    return 0;
}
