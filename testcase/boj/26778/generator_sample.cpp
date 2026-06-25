#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

char randomDifferent(char previous, int alphabetSize) {
    char c = char('a' + rnd.next(alphabetSize));
    if (c == previous) c = char('a' + (c - 'a' + 1) % alphabetSize);
    return c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int alphabetSize = rnd.next(1, 8);
    int n = rnd.next(1, 80);
    string s;

    if (mode == 0) {
        alphabetSize = rnd.next(2, 8);
        s.push_back(char('a' + rnd.next(alphabetSize)));
        while ((int)s.size() < n) {
            s.push_back(randomDifferent(s.back(), alphabetSize));
        }
    } else if (mode == 1) {
        char c = char('a' + rnd.next(26));
        s.assign(n, c);
    } else if (mode == 2) {
        alphabetSize = rnd.next(2, 6);
        char previous = 0;
        while ((int)s.size() < n) {
            char c = char('a' + rnd.next(alphabetSize));
            if (previous != 0 && c == previous) {
                c = char('a' + (c - 'a' + 1) % alphabetSize);
            }
            int runLength = rnd.next(1, 12);
            while (runLength-- > 0 && (int)s.size() < n) {
                s.push_back(c);
            }
            previous = c;
        }
    } else if (mode == 3) {
        alphabetSize = rnd.next(2, 4);
        for (int i = 0; i < n; ++i) {
            s.push_back(char('a' + rnd.next(alphabetSize)));
        }
    } else if (mode == 4) {
        alphabetSize = rnd.next(2, 8);
        s.push_back(char('a' + rnd.next(alphabetSize)));
        while ((int)s.size() < n) {
            if (rnd.next(100) < 35) {
                s.push_back(s.back());
            } else {
                s.push_back(randomDifferent(s.back(), alphabetSize));
            }
        }
    } else {
        vector<string> pieces = {"mama", "anna", "zorro", "ojojoj", "shellless"};
        string piece = rnd.any(pieces);
        while ((int)s.size() < n) {
            if (rnd.next(100) < 60) {
                s += piece;
            } else {
                s.push_back(char('a' + rnd.next(26)));
            }
        }
        s.resize(n);
    }

    println(s);
    return 0;
}
