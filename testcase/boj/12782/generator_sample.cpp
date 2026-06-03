#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomBits(int n, double oneProb) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(rnd.next() < oneProb ? '1' : '0');
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 50);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(5);
        int n = rnd.next(1, 60);
        if (rnd.next(10) == 0) {
            n = rnd.next(61, 200);
        }

        string a;
        string b;

        if (mode == 0) {
            double oneProb = rnd.next(0.0, 1.0);
            a = randomBits(n, oneProb);
            b = a;
        } else if (mode == 1) {
            a = randomBits(n, rnd.next(0.0, 1.0));
            b = a;
            for (char& ch : b) {
                ch = ch == '0' ? '1' : '0';
            }
        } else {
            a = randomBits(n, rnd.next(0.0, 1.0));
            b = a;

            vector<int> positions(n);
            for (int i = 0; i < n; ++i) {
                positions[i] = i;
            }
            shuffle(positions.begin(), positions.end());

            int changed = rnd.next(1, n);
            if (mode == 2) {
                changed -= changed % 2;
                if (changed == 0) {
                    changed = 1;
                }
            }

            for (int i = 0; i < changed; ++i) {
                int pos = positions[i];
                if (mode == 2 && i < changed / 2) {
                    a[pos] = '0';
                    b[pos] = '1';
                } else if (mode == 2) {
                    a[pos] = '1';
                    b[pos] = '0';
                } else if (mode == 3) {
                    a[pos] = rnd.next(4) == 0 ? '1' : '0';
                    b[pos] = '1';
                } else {
                    b[pos] = b[pos] == '0' ? '1' : '0';
                }
            }

            if (mode == 4 && n >= 2) {
                int prefix = rnd.next(1, min(n, 10));
                for (int i = 0; i < prefix; ++i) {
                    a[i] = '0';
                    b[i] = rnd.next(2) == 0 ? '0' : '1';
                }
            }
        }

        println(a, b);
    }

    return 0;
}
