#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char randomLower(int alphabetSize) {
    return char('a' + rnd.next(0, alphabetSize - 1));
}

char differentLower(char c, int alphabetSize) {
    if (alphabetSize == 1) {
        return c == 'a' ? 'b' : 'a';
    }

    char d = randomLower(alphabetSize);
    while (d == c) {
        d = randomLower(alphabetSize);
    }
    return d;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 5) {
        vector<int> edgeLengths = {1, 2, 99, 100};
        n = rnd.any(edgeLengths);
    } else {
        n = rnd.next(1, 30);
    }

    vector<int> alphabetSizes = {1, 2, 3, 5, 26};
    int alphabetSize = rnd.any(alphabetSizes);
    string s;
    string t;
    s.reserve(n);
    t.reserve(n);

    for (int i = 0; i < n; ++i) {
        s += randomLower(alphabetSize);
    }
    t = s;

    if (mode == 0) {
        // Hamming distance 0.
    } else if (mode == 1) {
        int pos = rnd.next(0, n - 1);
        t[pos] = differentLower(s[pos], alphabetSize);
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            t[i] = differentLower(s[i], alphabetSize);
        }
    } else if (mode == 3) {
        int period = rnd.next(2, 5);
        for (int i = 0; i < n; ++i) {
            if (i % period == 0) {
                t[i] = differentLower(s[i], alphabetSize);
            }
        }
    } else {
        double mismatchProbability = rnd.next(0.0, 1.0);
        for (int i = 0; i < n; ++i) {
            if (rnd.next() < mismatchProbability) {
                t[i] = differentLower(s[i], alphabetSize);
            }
        }
    }

    println(n);
    println(s);
    println(t);

    return 0;
}
