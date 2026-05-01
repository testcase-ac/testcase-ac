#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of test cases: small for manual check, but >=1
    int T = rnd.next(1, 5);
    println(T);
    const string faces = "WORBGY";
    // prebuilt solved lines
    string solved_row = "W W W O O O R R R B B B G G G Y Y Y";
    for (int tc = 0; tc < T; tc++) {
        // print the solved cube state (3 rows)
        println(solved_row);
        println(solved_row);
        println(solved_row);
        // decide manipulation string length with varied tiers
        int prob = rnd.next(1, 100);
        int len;
        if (prob <= 30) {
            // small tests
            len = rnd.next(1, 5);
        } else if (prob <= 70) {
            // medium-small
            len = rnd.next(6, 20);
        } else if (prob <= 90) {
            // medium
            len = rnd.next(21, 100);
        } else {
            // occasional large
            len = rnd.next(101, 1000);
        }
        // build and print the manipulation string
        string ops;
        ops.reserve(len);
        for (int i = 0; i < len; i++) {
            ops.push_back(rnd.any(faces));
        }
        println(ops);
    }
    return 0;
}
