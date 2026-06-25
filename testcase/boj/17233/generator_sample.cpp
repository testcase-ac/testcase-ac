#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

string randomString(int length, const string& alphabet) {
    string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result += rnd.any(alphabet);
    }
    return result;
}

string periodicString(int length, const string& period) {
    string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result += period[i % (int)period.size()];
    }
    return result;
}

pair<int, int> randomSubstringRange(int sLength, int maxLength) {
    int left = rnd.next(0, sLength - 1);
    int length = rnd.next(1, min(maxLength, sLength - left));
    return {left, length};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        s = randomString(rnd.next(1, 28), "abc");
    } else if (mode == 1) {
        string base = randomString(rnd.next(2, 6), "ab");
        s = periodicString(rnd.next(12, 60), base);
    } else if (mode == 2) {
        string left = randomString(rnd.next(4, 10), "abcd");
        string middle = randomString(rnd.next(4, 10), "xyz");
        s = left + middle + left.substr(0, rnd.next(1, (int)left.size()));
    } else if (mode == 3) {
        s = string(rnd.next(15, 80), 'a');
        for (int i = 0; i < (int)s.size(); ++i) {
            if (rnd.next(0, 9) == 0) s[i] = 'b';
        }
    } else if (mode == 4) {
        s = randomString(rnd.next(35, 120), "abcdefghijklmnopqrstuvwxyz");
    } else {
        string prefix = randomString(rnd.next(3, 8), "abcde");
        string center = randomString(rnd.next(8, 18), "mnop");
        string suffix = randomString(rnd.next(3, 8), "vwxyz");
        s = prefix + center + suffix;
    }

    int n = rnd.next(1, min(100, max(1, (int)s.size())));
    vector<string> patterns;
    patterns.reserve(n);

    int longPatternLimit = mode == 4 ? 40 : 20;
    for (int i = 0; i < n; ++i) {
        auto [left, length] = randomSubstringRange((int)s.size(), longPatternLimit);
        patterns.push_back(s.substr(left, length));
    }

    if (n >= 2 && rnd.next(0, 1)) {
        patterns[1] = patterns[0];
    }
    if (n >= 3) {
        int left = rnd.next(0, (int)s.size() - 1);
        int outerLength = rnd.next(1, min((int)s.size() - left, longPatternLimit));
        string outer = s.substr(left, outerLength);
        patterns[2] = outer;
        if (n >= 4) {
            int innerLeft = rnd.next(0, (int)outer.size() - 1);
            int innerLength = rnd.next(1, (int)outer.size() - innerLeft);
            patterns[3] = outer.substr(innerLeft, innerLength);
        }
    }

    shuffle(patterns.begin(), patterns.end());

    println(n);
    for (const string& pattern : patterns) {
        println((int)pattern.size(), pattern);
    }
    println((int)s.size(), s);

    return 0;
}
