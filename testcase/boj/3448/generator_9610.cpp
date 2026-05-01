#include "testlib.h"
using namespace std;

string makeRatioLine(int total, int recognized) {
    string s;
    // first put recognized characters (non-#)
    for (int i = 0; i < recognized; ++i) {
        char c = 'A' + rnd.next(0, 25);
        s += c;
    }
    // then put unrecognized characters '#'
    for (int i = recognized; i < total; ++i) {
        s += '#';
    }
    // shuffle to mix positions
    shuffle(s.begin(), s.end());
    return s;
}

string makeAllRecognizedLine(int len) {
    string s;
    for (int i = 0; i < len; ++i) {
        int mode = rnd.next(0, 2); // 0: lower, 1: upper, 2: digit
        char c;
        if (mode == 0) c = 'a' + rnd.next(0, 25);
        else if (mode == 1) c = 'A' + rnd.next(0, 25);
        else c = '0' + rnd.next(0, 9);
        s += c;
    }
    return s;
}

string makeAllHashLine(int len) {
    return string(len, '#');
}

string makeRandomMixedLine(int len, int hashPercent) {
    string punct = ".,;:!?";
    string s;
    for (int i = 0; i < len; ++i) {
        int mode = rnd.next(0, 4); // 0: lower, 1: upper, 2: digit, 3: space, 4: punct
        char c;
        if (mode == 0) c = 'a' + rnd.next(0, 25);
        else if (mode == 1) c = 'A' + rnd.next(0, 25);
        else if (mode == 2) c = '0' + rnd.next(0, 9);
        else if (mode == 3) c = ' ';
        else c = rnd.any(punct);

        // turn some characters into '#' (unrecognized)
        if (c != '#' && rnd.next(100) < hashPercent) c = '#';

        s += c;
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = rnd.next(1, 4); // number of test cases, small for readability
    vector<vector<string>> tests;
    tests.reserve(N);

    // pre-defined ratio patterns
    vector<pair<int,int>> integerRatios = {
        {1,2}, // 50%
        {1,4}, // 25%
        {3,4}, // 75%
        {1,5}, // 20%
        {2,5}, // 40%
        {3,5}, // 60%
        {4,5}  // 80%
    };
    vector<pair<int,int>> fractionalRatios = {
        {1,3}, // 33.3...
        {2,3}, // 66.6...
        {1,6}, // 16.6...
        {5,6}, // 83.3...
        {2,7}, // ~28.6
        {5,7}  // ~71.4
    };

    for (int ti = 0; ti < N; ++ti) {
        int type = rnd.next(0, 4); // 0..4
        vector<string> lines;

        if (type == 0) {
            // All recognized characters (100% efficiency)
            int L = rnd.next(1, 3); // 1-3 lines
            for (int i = 0; i < L; ++i) {
                int len = rnd.next(3, 15);
                lines.push_back(makeAllRecognizedLine(len));
            }
        } else if (type == 1) {
            // All '#', 0% efficiency
            int L = rnd.next(1, 2); // 1-2 lines
            for (int i = 0; i < L; ++i) {
                int len = rnd.next(3, 15);
                lines.push_back(makeAllHashLine(len));
            }
        } else if (type == 2) {
            // Integer percentage but not trivial 0 or 100
            pair<int,int> pr = rnd.any(integerRatios);
            int R = pr.first;
            int A = pr.second;
            lines.push_back(makeRatioLine(A, R));
        } else if (type == 3) {
            // Fractional percentage requiring proper rounding
            pair<int,int> pr = rnd.any(fractionalRatios);
            int R = pr.first;
            int A = pr.second;
            lines.push_back(makeRatioLine(A, R));
        } else {
            // Random mixed test with several lines
            int L = rnd.next(2, 4); // 2-4 lines
            int hashPercent = rnd.next(10, 60); // 10% to 60% '#'
            for (int i = 0; i < L; ++i) {
                int len = rnd.next(3, 20);
                lines.push_back(makeRandomMixedLine(len, hashPercent));
            }
        }

        tests.push_back(lines);
    }

    println(N);
    for (int ti = 0; ti < N; ++ti) {
        for (string &s : tests[ti]) {
            println(s);
        }
        if (ti + 1 < N) println(""); // blank line between test cases
    }

    return 0;
}
