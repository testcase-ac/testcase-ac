#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, mode == 5 ? 60 : 24);

    string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lowercase = "abcdefghijklmnopqrstuvwxyz";
    string a;
    a.reserve(n);

    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            a += uppercase[rnd.next(0, 25)];
        } else if (mode == 1) {
            a += lowercase[rnd.next(0, 25)];
        } else if (mode == 2) {
            a += rnd.next(0, 1) ? uppercase[rnd.next(0, 25)] : lowercase[rnd.next(0, 25)];
        } else if (mode == 3) {
            char base = uppercase[rnd.next(0, 5)];
            a += rnd.next(0, 2) == 0 ? char(base - 'A' + 'a') : base;
        } else {
            char base = uppercase[rnd.next(0, 25)];
            a += rnd.next(0, 3) == 0 ? char(base - 'A' + 'a') : base;
        }
    }

    vector<char> letters(uppercase.begin(), uppercase.end());
    shuffle(letters.begin(), letters.end());

    int count;
    if (mode == 4) {
        count = 26;
    } else if (mode == 5) {
        count = rnd.next(10, 26);
    } else {
        count = rnd.next(1, 8);
    }

    vector<char> b(letters.begin(), letters.begin() + count);

    println(a);
    for (int i = 0; i < (int)b.size(); ++i) {
        if (i > 0) cout << ' ';
        cout << b[i];
    }
    cout << '\n';

    return 0;
}
