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

string transformByBlocks(const string& s) {
    vector<string> blocks;
    int pos = 0;
    while (pos < static_cast<int>(s.size())) {
        int remaining = static_cast<int>(s.size()) - pos;
        int len = rnd.next(1, min(remaining, rnd.next(1, 6)));
        blocks.push_back(s.substr(pos, len));
        pos += len;
    }

    string t;
    for (int i = static_cast<int>(blocks.size()) - 1; i >= 0; --i) {
        t += blocks[i];
    }
    return t;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    if (rnd.next(0, 3) != 0) {
        alphabet = alphabet.substr(0, rnd.next(1, 5));
    }

    string s = randomString(n, alphabet);
    string t;

    if (mode == 0) {
        t = transformByBlocks(s);
    } else if (mode == 1) {
        t = transformByBlocks(s);
        if (n >= 2) {
            int i = rnd.next(0, n - 1);
            int j = rnd.next(0, n - 1);
            swap(t[i], t[j]);
        }
    } else if (mode == 2) {
        t = s;
        shuffle(t.begin(), t.end());
    } else if (mode == 3) {
        char c = rnd.any(alphabet);
        s.assign(n, c);
        t.assign(n, c);
    } else if (mode == 4) {
        t = randomString(n, alphabet);
    } else {
        n = rnd.next(1, 8);
        s = randomString(n, "ab");
        t = transformByBlocks(s);
        if (rnd.next(0, 1) == 1 && n >= 2) {
            int i = rnd.next(0, n - 2);
            swap(t[i], t[i + 1]);
        }
    }

    println(n);
    println(s);
    println(t);

    return 0;
}
