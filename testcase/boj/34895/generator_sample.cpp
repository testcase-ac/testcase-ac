#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomBits(int n, int onesPercent) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(rnd.next(1, 100) <= onesPercent ? '1' : '0');
    }
    return s;
}

string alternatingBits(int n, char first) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back((i % 2 == 0) ? first : (first == '0' ? '1' : '0'));
    }
    return s;
}

string blockyBits(int n) {
    string s;
    s.reserve(n);
    char bit = rnd.next(0, 1) ? '1' : '0';
    while (static_cast<int>(s.size()) < n) {
        int remaining = n - static_cast<int>(s.size());
        int run = rnd.next(1, min(remaining, rnd.next(2, 8)));
        s.append(run, bit);
        if (rnd.next(0, 99) < 75) {
            bit = bit == '0' ? '1' : '0';
        }
    }
    return s;
}

string deBruijnBinary(int order) {
    int alphabetSize = 2;
    vector<int> a(alphabetSize * order);
    string sequence;

    auto db = [&](auto&& self, int t, int p) -> void {
        if (t > order) {
            if (order % p == 0) {
                for (int i = 1; i <= p; ++i) {
                    sequence.push_back(static_cast<char>('0' + a[i]));
                }
            }
            return;
        }

        a[t] = a[t - p];
        self(self, t + 1, p);
        for (int j = a[t - p] + 1; j < alphabetSize; ++j) {
            a[t] = j;
            self(self, t + 1, t);
        }
    };

    db(db, 1, 1);
    sequence.append(sequence.substr(0, order - 1));
    return sequence;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    string s;

    if (mode == 0) {
        n = rnd.next(1, 6);
        s = randomBits(n, rnd.next(0, 100));
    } else if (mode == 1) {
        n = rnd.next(2, 40);
        s.assign(n, rnd.next(0, 1) ? '1' : '0');
    } else if (mode == 2) {
        n = rnd.next(2, 60);
        s = alternatingBits(n, rnd.next(0, 1) ? '1' : '0');
    } else if (mode == 3) {
        n = rnd.next(8, 120);
        s = randomBits(n, rnd.any(vector<int>{5, 20, 50, 80, 95}));
    } else if (mode == 4) {
        n = rnd.next(8, 120);
        s = blockyBits(n);
    } else if (mode == 5) {
        int order = rnd.next(2, 7);
        s = deBruijnBinary(order);
        if (rnd.next(0, 1)) {
            reverse(s.begin(), s.end());
        }
        n = static_cast<int>(s.size());
    } else {
        n = rnd.next(80, 400);
        s = randomBits(n, 50);
    }

    println(n);
    println(s);
    return 0;
}
