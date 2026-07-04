#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> pow3(8, 1);
    for (int i = 1; i < (int)pow3.size(); ++i) {
        pow3[i] = pow3[i - 1] * 3;
    }

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 2;
    } else {
        n = rnd.next(1, 6);
    }

    int len = pow3[n];
    int q = rnd.next(1, 35);
    string t(len, 'A');

    if (mode == 0) {
        for (int i = 0; i < len; ++i) {
            t[i] = rnd.next(0, 1) == 0 ? 'A' : 'B';
        }
    } else if (mode == 1) {
        char ch = rnd.next(0, 1) == 0 ? 'A' : 'B';
        t.assign(len, ch);
    } else if (mode == 2) {
        for (int i = 0; i < len; i += 3) {
            char majority = rnd.next(0, 1) == 0 ? 'A' : 'B';
            char minority = majority == 'A' ? 'B' : 'A';
            int odd = rnd.next(0, 2);
            for (int j = 0; j < 3; ++j) {
                t[i + j] = (j == odd ? minority : majority);
            }
        }
    } else if (mode == 3) {
        int period = pow3[rnd.next(0, n)];
        for (int i = 0; i < len; ++i) {
            t[i] = ((i / period) % 2 == 0) ? 'A' : 'B';
        }
    } else {
        double bProbability = rnd.next(0.15, 0.85);
        for (int i = 0; i < len; ++i) {
            t[i] = rnd.next() < bProbability ? 'B' : 'A';
        }
    }

    vector<int> queries;
    queries.reserve(q);
    if (mode == 4) {
        int hot = rnd.next(1, len);
        for (int i = 0; i < q; ++i) {
            int delta = rnd.next(-2, 2);
            int p = hot + delta;
            if (p < 1) p = 1;
            if (p > len) p = len;
            queries.push_back(p);
        }
    } else if (mode == 5) {
        for (int i = 0; i < q; ++i) {
            int block = rnd.next(0, len / 3 - 1);
            queries.push_back(block * 3 + rnd.next(1, 3));
        }
    } else {
        for (int i = 0; i < q; ++i) {
            queries.push_back(rnd.next(1, len));
        }
    }

    println(n, q);
    println(t);
    for (int p : queries) {
        println(p);
    }

    return 0;
}
