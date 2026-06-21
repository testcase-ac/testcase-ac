#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int pickCount(int mode) {
    if (mode == 0) {
        return rnd.next(1, 6);
    }
    if (mode == 1) {
        vector<int> values = {1, 2, 3, 7, 31, 998, 1024, 1000000000};
        return rnd.any(values);
    }
    if (mode == 2) {
        return rnd.next(999999900, 1000000000);
    }
    return rnd.next(1, 1000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 5);
    } else if (mode == 1) {
        n = rnd.next(6, 15);
    } else if (mode == 2) {
        n = rnd.next(16, 40);
    } else if (mode == 3) {
        n = rnd.next(2, 30);
    } else if (mode == 4) {
        n = rnd.next(20, 80);
    } else {
        n = rnd.next(3, 26);
    }

    vector<pair<char, int>> runs;
    runs.reserve(n);

    if (mode == 3) {
        char a = rnd.next('a', 'z');
        char b = rnd.next('a', 'z');
        while (b == a) {
            b = rnd.next('a', 'z');
        }
        for (int i = 0; i < n; ++i) {
            runs.push_back({i % 2 == 0 ? a : b, pickCount(rnd.next(0, 3))});
        }
    } else if (mode == 5) {
        string letters = "abcdefghijklmnopqrstuvwxyz";
        if (rnd.next(0, 1)) {
            reverse(letters.begin(), letters.end());
        }
        int offset = rnd.next(0, 25);
        for (int i = 0; i < n; ++i) {
            runs.push_back({letters[(offset + i) % 26], pickCount(rnd.next(0, 2))});
        }
    } else {
        int alphabetSize = rnd.next(2, 26);
        string letters = "abcdefghijklmnopqrstuvwxyz";
        shuffle(letters.begin(), letters.end());
        letters.resize(alphabetSize);

        char previous = '\0';
        for (int i = 0; i < n; ++i) {
            char c = rnd.any(letters);
            while (c == previous) {
                c = rnd.any(letters);
            }
            runs.push_back({c, pickCount(rnd.next(0, 3))});
            previous = c;
        }
    }

    println(n);
    for (auto [c, v] : runs) {
        println(string(1, c), v);
    }

    return 0;
}
