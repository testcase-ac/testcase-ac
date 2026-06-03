#include "testlib.h"

#include <string>

using namespace std;

int randomStep() {
    int options[] = {1, 2, 5};
    return options[rnd.next(0, 2)];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    string s;

    if (mode == 0) {
        char c = char('A' + rnd.next(0, 25));
        s.assign(n, c);
    } else if (mode == 1) {
        char a = char('A' + rnd.next(0, 25));
        char b = char('A' + (a - 'A' + 13) % 26);
        for (int i = 0; i < n; ++i) s += (i % 2 == 0 ? a : b);
    } else if (mode == 2) {
        int cur = rnd.next(0, 25);
        for (int i = 0; i < n; ++i) {
            s += char('A' + cur);
            cur = (cur + randomStep()) % 26;
        }
    } else if (mode == 3) {
        int cur = rnd.next(0, 25);
        for (int i = 0; i < n; ++i) {
            s += char('A' + cur);
            cur = (cur + 26 - randomStep()) % 26;
        }
    } else if (mode == 4) {
        string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int limit = rnd.next(1, 26);
        for (int i = 0; i < n; ++i) s += alphabet[rnd.next(0, limit - 1)];
    } else {
        n = rnd.next(31, 100);
        for (int i = 0; i < n; ++i) s += char('A' + rnd.next(0, 25));
    }

    println(s);
    return 0;
}
