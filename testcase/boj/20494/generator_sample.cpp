#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomString(int length, int alphabetSize) {
    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i) {
        s.push_back(char('A' + rnd.next(0, alphabetSize - 1)));
    }
    return s;
}

string runString(int length, int alphabetSize) {
    string s;
    s.reserve(length);
    char current = char('A' + rnd.next(0, alphabetSize - 1));
    while ((int)s.size() < length) {
        int run = rnd.next(1, min(8, length - (int)s.size()));
        if (rnd.next(0, 2) == 0) {
            current = char('A' + rnd.next(0, alphabetSize - 1));
        }
        s.append(run, current);
    }
    return s;
}

string cyclicString(int length, int alphabetSize) {
    string s;
    s.reserve(length);
    int start = rnd.next(0, alphabetSize - 1);
    int step = rnd.next(1, max(1, alphabetSize - 1));
    for (int i = 0; i < length; ++i) {
        s.push_back(char('A' + (start + i * step) % alphabetSize));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else if (mode == 2) {
        n = rnd.next(6, 15);
    } else if (mode == 3) {
        n = rnd.next(16, 30);
    } else if (mode == 4) {
        n = rnd.next(31, 60);
    } else {
        n = rnd.next(61, 100);
    }

    int alphabetSize;
    if (mode == 0) {
        alphabetSize = rnd.next(1, 3);
    } else if (mode == 5) {
        alphabetSize = rnd.next(20, 26);
    } else {
        alphabetSize = rnd.next(2, 12);
    }

    vector<string> wants;
    wants.reserve(n);
    for (int i = 0; i < n; ++i) {
        int length;
        if (mode == 0) {
            length = rnd.next(1, 100);
        } else if (mode == 1) {
            length = rnd.next(1, 8);
        } else if (mode == 4) {
            length = rnd.next(15, 35);
        } else if (mode == 5) {
            length = rnd.next(1, 25);
        } else {
            length = rnd.next(3, 20);
        }

        int pattern = rnd.next(0, 3);
        if (pattern == 0) {
            wants.push_back(randomString(length, alphabetSize));
        } else if (pattern == 1) {
            wants.push_back(runString(length, alphabetSize));
        } else if (pattern == 2) {
            wants.push_back(cyclicString(length, alphabetSize));
        } else {
            string base = cyclicString(length, alphabetSize);
            reverse(base.begin(), base.end());
            wants.push_back(base);
        }
    }

    println(n);
    for (const string& s : wants) {
        println(s);
    }
    return 0;
}
