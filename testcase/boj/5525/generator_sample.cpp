#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

static string alternating(int length, char first) {
    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i) {
        s.push_back((i % 2 == 0) ? first : (first == 'I' ? 'O' : 'I'));
    }
    return s;
}

static string randomIO(int length) {
    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i) {
        s.push_back(rnd.next(2) == 0 ? 'I' : 'O');
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 10);
    int minM = 2 * n + 1;
    int m = rnd.next(minM, minM + rnd.next(0, 35));

    int mode = rnd.next(5);
    string s;

    if (mode == 0) {
        s = randomIO(m);
    } else if (mode == 1) {
        s = alternating(m, 'I');
    } else if (mode == 2) {
        s = alternating(m, 'O');
    } else if (mode == 3) {
        s.assign(m, rnd.next(2) == 0 ? 'I' : 'O');
    } else {
        s = randomIO(m);
        string p = alternating(minM, 'I');
        int pos = rnd.next(0, m - minM);
        for (int i = 0; i < minM; ++i) {
            s[pos + i] = p[i];
        }
    }

    if (rnd.next(4) == 0) {
        vector<int> positions;
        for (int i = 0; i < m; ++i) {
            positions.push_back(i);
        }
        shuffle(positions.begin(), positions.end());
        int flips = rnd.next(1, max(1, m / 6));
        for (int i = 0; i < flips; ++i) {
            char& c = s[positions[i]];
            c = (c == 'I') ? 'O' : 'I';
        }
    }

    println(n);
    println(m);
    println(s);
    return 0;
}
