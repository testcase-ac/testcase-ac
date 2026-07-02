#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

long long randomTime(int mode) {
    if (mode == 0) return rnd.next(1LL, 12LL);
    if (mode == 1) return rnd.next(13LL, 1000LL);
    if (mode == 2) return rnd.next(1000000000LL, 1000000000000LL);
    return rnd.next(999999999999000000LL, 1000000000000000000LL);
}

string randomString(int length, int mode) {
    const string colors = "WRG";
    string s;
    s.reserve(length);

    if (mode == 0) {
        char c = colors[rnd.next(0, 2)];
        s.assign(length, c);
    } else if (mode == 1) {
        string pattern = rnd.any(vector<string>{"WRG", "WGR", "RG", "RRGG", "WWRG"});
        for (int i = 0; i < length; ++i) s.push_back(pattern[i % pattern.size()]);
    } else if (mode == 2) {
        char dominant = colors[rnd.next(0, 2)];
        for (int i = 0; i < length; ++i) {
            if (rnd.next(0, 99) < 70) {
                s.push_back(dominant);
            } else {
                s.push_back(colors[rnd.next(0, 2)]);
            }
        }
    } else {
        for (int i = 0; i < length; ++i) s.push_back(colors[rnd.next(0, 2)]);
    }

    int rotation = rnd.next(0, length - 1);
    rotate(s.begin(), s.begin() + rotation, s.end());
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 20);
    println(t);

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int sizeMode = rnd.next(0, 4);
        int length;
        if (caseIndex == 0) {
            length = 1;
        } else if (sizeMode <= 1) {
            length = rnd.next(2, 12);
        } else if (sizeMode <= 3) {
            length = rnd.next(13, 80);
        } else {
            length = rnd.next(81, 240);
        }

        int patternMode = rnd.next(0, 3);
        long long n = randomTime(rnd.next(0, 3));
        println(randomString(length, patternMode), n);
    }

    return 0;
}
