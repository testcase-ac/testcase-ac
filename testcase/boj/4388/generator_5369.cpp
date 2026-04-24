#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases (excluding the terminating "0 0")
    int T = rnd.next(1, 10);
    vector<pair<string, string>> tests;

    for (int ti = 0; ti < T; ti++) {
        // Hyper-parameter for length bias: -1 (shorter), 0 (uniform), +1 (longer)
        int lb1 = rnd.next(-1, 1), lb2 = rnd.next(-1, 1);
        int len1 = rnd.wnext(10, lb1) + 1; // 1..10
        int len2 = rnd.wnext(10, lb2) + 1; // 1..10

        // Hyper-parameter for digit bias: -1 (small digits), 0 (uniform), +1 (large digits)
        int db1 = rnd.next(-1, 1), db2 = rnd.next(-1, 1);

        // Generate first number
        string s1;
        s1.reserve(len1);
        for (int i = 0; i < len1; i++) {
            int d;
            if (i == 0 && len1 > 1) {
                // leading digit 1..9
                d = rnd.wnext(9, db1) + 1;
            } else {
                // any digit 0..9
                d = rnd.wnext(10, db1);
            }
            s1.push_back(char('0' + d));
        }

        // Generate second number
        string s2;
        s2.reserve(len2);
        for (int i = 0; i < len2; i++) {
            int d;
            if (i == 0 && len2 > 1) {
                d = rnd.wnext(9, db2) + 1;
            } else {
                d = rnd.wnext(10, db2);
            }
            s2.push_back(char('0' + d));
        }

        // Avoid generating the terminating "0 0" as a test case
        if (s1 == "0" && s2 == "0") {
            s2[0] = '1';
        }

        tests.emplace_back(s1, s2);
    }

    // Output all test cases and the terminating line
    for (auto &p : tests) {
        println(p.first, p.second);
    }
    println(0, 0);

    return 0;
}
