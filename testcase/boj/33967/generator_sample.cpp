#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode <= 4) {
        n = rnd.next(3, 30);
    } else if (mode <= 6) {
        n = rnd.next(31, 300);
    } else {
        n = rnd.next(1000, 200000);
    }

    string alphabet = "25[]";
    if (mode == 1) alphabet = "25";
    if (mode == 2) alphabet = "[]";
    if (mode == 3) alphabet = "555222";
    if (mode == 4) alphabet = "[[]]25";

    string s(n, ' ');
    s[0] = '[';
    s[n - 1] = ']';
    for (int i = 1; i + 1 < n; ++i) {
        s[i] = rnd.any(alphabet);
    }

    println(n);
    println(s);

    return 0;
}
