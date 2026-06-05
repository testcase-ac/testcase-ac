#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomNoise(int n) {
    const string letters = "ABCDFGIJKLMNOPQRSTUVXYZ";
    string s;
    for (int i = 0; i < n; ++i) s += rnd.any(letters);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    string s;

    if (mode == 0) {
        int n = rnd.next(1, 25);
        s = randomNoise(n);
    } else if (mode == 1) {
        int w = rnd.next(1, 5);
        int h = rnd.next(1, 5);
        int e = rnd.next(0, 10);
        s = string(w, 'W') + randomNoise(rnd.next(0, 3)) + string(h, 'H') + string(e, 'E');
    } else if (mode == 2) {
        int copies = rnd.next(1, 5);
        for (int i = 0; i < copies; ++i) {
            s += "WH";
            s += string(rnd.next(2, 5), 'E');
            s += randomNoise(rnd.next(0, 2));
        }
    } else if (mode == 3) {
        int n = rnd.next(4, 28);
        const string core = "WHEE";
        for (int i = 0; i < n; ++i) s += rnd.any(core);
    } else if (mode == 4) {
        int w = rnd.next(1, 4);
        int h = rnd.next(1, 4);
        int e = rnd.next(2, 12);
        s = string(e, 'E') + string(h, 'H') + string(w, 'W');
    } else if (mode == 5) {
        int n = rnd.next(4, 28);
        const string letters = "WHEEABCDEFG";
        for (int i = 0; i < n; ++i) s += rnd.any(letters);
    } else {
        vector<char> parts;
        int blocks = rnd.next(2, 7);
        for (int i = 0; i < blocks; ++i) {
            char c = rnd.any(string("WHEA"));
            int len = rnd.next(1, 4);
            for (int j = 0; j < len; ++j) parts.push_back(c);
        }
        shuffle(parts.begin(), parts.end());
        s.assign(parts.begin(), parts.end());
    }

    println((int)s.size());
    println(s);

    return 0;
}
