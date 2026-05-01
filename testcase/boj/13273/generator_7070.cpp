#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

string toRoman(int num) {
    vector<pair<int, string>> romanMap = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100,  "C"}, {90,  "XC"}, {50,  "L"},  {40,  "XL"},
        {10,   "X"}, {9,   "IX"}, {5,   "V"},  {4,   "IV"},
        {1,    "I"}
    };
    string res;
    for (auto &p : romanMap) {
        while (num >= p.first) {
            num -= p.first;
            res += p.second;
        }
    }
    return res;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);

    vector<string> tests;
    bool hasRoman = false, hasArabic = false;

    for (int i = 0; i < T; i++) {
        // Sample number with different ranges
        int n;
        double r = rnd.next();
        if (r < 0.2) {
            n = rnd.next(1, 10);
        } else if (r < 0.6) {
            n = rnd.next(11, 100);
        } else if (r < 0.9) {
            n = rnd.next(101, 1000);
        } else {
            n = rnd.next(1001, 3999);
        }

        // Decide format
        bool wantRoman = rnd.next(0, 1) == 1;
        if (wantRoman) {
            tests.push_back(toRoman(n));
            hasRoman = true;
        } else {
            tests.push_back(to_string(n));
            hasArabic = true;
        }
    }

    // Ensure at least one of each type if possible
    if (T >= 2) {
        if (!hasRoman) {
            // replace first entry with a Roman
            int val = rnd.next(1, 3999);
            tests[0] = toRoman(val);
        }
        if (!hasArabic) {
            int val = rnd.next(1, 3999);
            tests[1] = to_string(val);
        }
    }

    // Shuffle order for unpredictability
    shuffle(tests.begin(), tests.end());

    // Output test cases
    for (auto &s : tests) {
        println(s);
    }

    return 0;
}
