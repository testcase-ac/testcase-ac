#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomString(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(rnd.any(alphabet));
    }
    return s;
}

string palindromeLike(int n, const string& alphabet) {
    string s(n, 'a');
    for (int i = 0; i < (n + 1) / 2; ++i) {
        char c = rnd.any(alphabet);
        s[i] = c;
        s[n - 1 - i] = c;
    }

    int swaps = rnd.next(0, min(3, max(0, n - 1)));
    for (int i = 0; i < swaps; ++i) {
        int pos = rnd.next(0, n - 2);
        swap(s[pos], s[pos + 1]);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (rnd.next(0, 9) == 0) {
        n = rnd.next(80, 300);
    } else {
        n = rnd.next(1, 30);
    }

    vector<string> alphabets = {
        "a",
        "ab",
        "abc",
        "abcdef",
        "abcdefghijklmnopqrstuvwxyz",
    };
    string alphabet = rnd.any(alphabets);

    string s;
    if (mode == 0) {
        s = palindromeLike(n, alphabet);
    } else if (mode == 1) {
        s = randomString(n, alphabet);
    } else if (mode == 2) {
        s = string(n, rnd.any(alphabet));
        int changes = rnd.next(0, min(n, 5));
        for (int i = 0; i < changes; ++i) {
            s[rnd.next(0, n - 1)] = rnd.any(alphabet);
        }
    } else {
        s = palindromeLike(n, alphabet);
        int changes = rnd.next(1, min(n, 4));
        for (int i = 0; i < changes; ++i) {
            s[rnd.next(0, n - 1)] = rnd.any(alphabet);
        }
    }

    println(s);
    return 0;
}
