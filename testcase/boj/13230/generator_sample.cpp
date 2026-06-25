#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomBinaryString(int n) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += char('0' + rnd.next(0, 1));
    }
    return s;
}

string makeSourceFromTarget(const string& t, int mode) {
    string s = t;
    int n = int(s.size());

    if (mode == 0) {
        return s;
    }

    if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 45) {
                s[i] = '?';
            }
        }
        return s;
    }

    if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            if (t[i] == '1' && rnd.next(100) < 55) {
                s[i] = '0';
            } else if (rnd.next(100) < 25) {
                s[i] = '?';
            }
        }
        return s;
    }

    if (mode == 3) {
        vector<int> zeroInT, oneInT;
        for (int i = 0; i < n; ++i) {
            if (t[i] == '0') {
                zeroInT.push_back(i);
            } else {
                oneInT.push_back(i);
            }
        }
        if (!zeroInT.empty() && !oneInT.empty()) {
            shuffle(zeroInT.begin(), zeroInT.end());
            shuffle(oneInT.begin(), oneInT.end());
            int pairs = rnd.next(1, min(int(zeroInT.size()), int(oneInT.size())));
            for (int i = 0; i < pairs; ++i) {
                s[zeroInT[i]] = '1';
                s[oneInT[i]] = '0';
            }
        }
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 20) {
                s[i] = '?';
            }
        }
        return s;
    }

    if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            s[i] = rnd.any(string("01?"));
        }
        return s;
    }

    for (int i = 0; i < n; ++i) {
        s[i] = '1';
    }
    if (rnd.next(100) < 50) {
        int keepOnes = max(1, n - rnd.next(0, min(n - 1, 5)));
        for (int i = keepOnes; i < n; ++i) {
            s[i] = rnd.any(string("0?"));
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int c = rnd.next(12, 30);
    println(c);

    for (int tc = 0; tc < c; ++tc) {
        int n;
        if (tc == 0) {
            n = 1;
        } else if (tc == 1) {
            n = 2;
        } else if (tc == 2) {
            n = 100;
        } else {
            n = rnd.next(1, 30);
        }

        string t;
        int pattern = rnd.next(0, 4);
        if (pattern == 0) {
            t = string(n, '0');
        } else if (pattern == 1) {
            t = string(n, '1');
        } else if (pattern == 2) {
            t.reserve(n);
            for (int i = 0; i < n; ++i) {
                t += char('0' + (i % 2));
            }
        } else if (pattern == 3) {
            t.reserve(n);
            for (int i = 0; i < n; ++i) {
                t += char('0' + ((i + 1) % 2));
            }
        } else {
            t = randomBinaryString(n);
        }

        int mode = rnd.next(0, 5);
        string s = makeSourceFromTarget(t, mode);

        println(s);
        println(t);
    }

    return 0;
}
