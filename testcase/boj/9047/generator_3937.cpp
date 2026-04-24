#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 10);
    // Some known interesting numbers (not all digits same)
    vector<int> special = {6174, 2005, 1789, 1000, 9998, 2111};
    // Probability to pick from special set
    double p_special = rnd.next();
    // Bias parameter for weighted sampling of other numbers
    int bias = rnd.next(-2, 2);

    vector<int> tests;
    while ((int)tests.size() < T) {
        int n;
        if (rnd.next() < p_special) {
            n = rnd.any(special);
        } else {
            // Generate a number in [1000,9998] with some bias
            int x = rnd.wnext(8999, bias);
            n = 1000 + x;
        }
        // Build string with leading zeros if needed
        string s = to_string(n);
        while (s.size() < 4) s = "0" + s;
        // Exclude repdigits like 1111, 2222, ...
        bool allsame = true;
        for (int i = 1; i < 4; i++) {
            if (s[i] != s[0]) {
                allsame = false;
                break;
            }
        }
        if (allsame) continue;
        tests.push_back(n);
    }

    // Output
    println(T);
    for (int x : tests) {
        println(x);
    }
    return 0;
}
