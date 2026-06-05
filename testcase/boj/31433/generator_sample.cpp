#include "testlib.h"

#include <string>

using namespace std;

char patternChar(int pos, int phase) {
    static const string ksa = "KSA";
    return ksa[(pos + phase) % 3];
}

string patternString(int n, int phase) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(patternChar(i, phase));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string alphabet = "KSA";
    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 40);
    string s;

    if (mode == 0) {
        s = patternString(n, 0);
    } else if (mode == 1) {
        s = patternString(n, rnd.next(1, 2));
    } else if (mode == 2) {
        s.assign(n, rnd.any(alphabet));
    } else if (mode == 3) {
        s = patternString(n, 0);
        int edits = rnd.next(1, max(1, n / 4));
        for (int i = 0; i < edits; ++i) {
            int pos = rnd.next(n);
            char c = rnd.any(alphabet);
            while (c == s[pos]) {
                c = rnd.any(alphabet);
            }
            s[pos] = c;
        }
    } else if (mode == 4) {
        int blocks = rnd.next(1, min(n, 8));
        for (int block = 0; block < blocks; ++block) {
            int remaining = n - static_cast<int>(s.size());
            int len = block + 1 == blocks ? remaining : rnd.next(1, remaining - (blocks - block - 1));
            s.append(len, rnd.any(alphabet));
        }
    } else {
        for (int i = 0; i < n; ++i) {
            s.push_back(rnd.any(alphabet));
        }
    }

    println(s);
    return 0;
}
