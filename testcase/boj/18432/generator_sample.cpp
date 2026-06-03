#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string repeatChar(char c, int count) {
    return string(count, c);
}

string randomJOIString(int n) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += rnd.any(string("JOI"));
    }
    return s;
}

void addRandomNoise(string& s, int count) {
    for (int i = 0; i < count; ++i) {
        int pos = rnd.next(0, (int)s.size());
        s.insert(s.begin() + pos, rnd.any(string("JOI")));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k = 1;
    string s;

    if (mode == 0) {
        k = rnd.next(1, 8);
        s = repeatChar('J', k) + repeatChar('O', k) + repeatChar('I', k);
        addRandomNoise(s, rnd.next(0, 12));
    } else if (mode == 1) {
        k = rnd.next(1, 7);
        s = repeatChar('J', k) + repeatChar('O', k) + repeatChar('I', k);
        string prefix = randomJOIString(rnd.next(0, 8));
        string suffix = randomJOIString(rnd.next(0, 8));
        s = prefix + s + suffix;
    } else if (mode == 2) {
        k = rnd.next(1, 6);
        s = repeatChar('I', rnd.next(k, k + 5)) + repeatChar('O', rnd.next(k, k + 5)) +
            repeatChar('J', rnd.next(k, k + 5));
        addRandomNoise(s, rnd.next(0, 5));
    } else if (mode == 3) {
        k = rnd.next(1, 6);
        int missingType = rnd.next(0, 2);
        vector<int> counts(3);
        for (int i = 0; i < 3; ++i) counts[i] = rnd.next(k, k + 6);
        counts[missingType] = rnd.next(0, k - 1);
        s = repeatChar('J', counts[0]) + repeatChar('O', counts[1]) + repeatChar('I', counts[2]);
        shuffle(s.begin(), s.end());
    } else if (mode == 4) {
        int n = rnd.next(3, 35);
        k = rnd.next(1, n / 3);
        s = randomJOIString(n);
    } else {
        k = rnd.next(1, 10);
        vector<char> chars;
        for (int i = 0; i < k; ++i) {
            chars.push_back('J');
            chars.push_back('O');
            chars.push_back('I');
        }
        int extra = rnd.next(0, 20);
        for (int i = 0; i < extra; ++i) chars.push_back(rnd.any(string("JOI")));
        shuffle(chars.begin(), chars.end());
        s.assign(chars.begin(), chars.end());
    }

    int n = (int)s.size();
    println(n, k);
    println(s);

    return 0;
}
