#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string repeated(char ch, int length) {
    return string(length, ch);
}

string alternating(int length, const string& alphabet) {
    string result;
    result.reserve(length);
    int offset = rnd.next(static_cast<int>(alphabet.size()));
    for (int i = 0; i < length; ++i) {
        result.push_back(alphabet[(i + offset) % alphabet.size()]);
    }
    return result;
}

string randomPattern(int length, const string& alphabet) {
    string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result.push_back(rnd.any(alphabet));
    }
    return result;
}

string runPattern(int length) {
    string result;
    result.reserve(length);

    char last = 0;
    while (static_cast<int>(result.size()) < length) {
        char ch = rnd.any(string("abc"));
        if (last != 0 && ch == last) {
            ch = static_cast<char>('a' + (ch - 'a' + 1 + rnd.next(2)) % 3);
        }

        int remaining = length - static_cast<int>(result.size());
        int runLength = rnd.next(1, min(remaining, rnd.next(2, 7)));
        result.append(runLength, ch);
        last = ch;
    }

    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 10);
    println(n);

    for (int i = 0; i < n; ++i) {
        int mode = rnd.next(6);
        int length;
        string pattern;

        if (mode == 0) {
            length = 1;
            pattern = randomPattern(length, "abc");
        } else if (mode == 1) {
            length = rnd.next(2, 25);
            pattern = repeated(rnd.any(string("abc")), length);
        } else if (mode == 2) {
            length = rnd.next(2, 30);
            pattern = alternating(length, "ab");
        } else if (mode == 3) {
            length = rnd.next(3, 30);
            pattern = alternating(length, "abc");
        } else if (mode == 4) {
            length = rnd.next(2, 35);
            pattern = runPattern(length);
        } else {
            length = rnd.next(2, 40);
            string alphabet = rnd.next(2) == 0 ? string("ab") : string("abc");
            pattern = randomPattern(length, alphabet);
        }

        println(length);
        println(pattern);
    }

    return 0;
}
