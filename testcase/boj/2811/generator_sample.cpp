#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int cold() {
    return rnd.next(-100, -1);
}

int warm() {
    return rnd.next(0, 100);
}

void appendRun(vector<int>& a, int len, bool isCold) {
    for (int i = 0; i < len; ++i) {
        a.push_back(isCold ? cold() : warm());
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> a;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 25);
        appendRun(a, n, false);
    } else if (mode == 1) {
        int n = rnd.next(1, 25);
        appendRun(a, n, true);
    } else if (mode == 2) {
        int n = rnd.next(1, 35);
        for (int i = 0; i < n; ++i) {
            bool isCold = ((i + rnd.next(0, 1)) % 2 == 0);
            a.push_back(isCold ? cold() : warm());
        }
    } else if (mode == 3) {
        int periods = rnd.next(2, 5);
        int longest = rnd.next(2, 6);
        appendRun(a, rnd.next(0, 5), false);
        for (int i = 0; i < periods; ++i) {
            int coldLen = (rnd.next(0, 2) == 0 ? longest : rnd.next(1, longest));
            int warmLen = rnd.next(1, 6);
            appendRun(a, coldLen, true);
            appendRun(a, warmLen, false);
        }
    } else if (mode == 4) {
        int periods = rnd.next(3, 7);
        appendRun(a, rnd.next(0, 3), false);
        for (int i = 0; i < periods; ++i) {
            int coldLen = rnd.next(1, 5);
            int warmLen = rnd.next(1, 3);
            appendRun(a, coldLen, true);
            appendRun(a, warmLen, false);
        }
    } else {
        int blocks = rnd.next(4, 10);
        bool isCold = rnd.next(0, 1);
        for (int i = 0; i < blocks; ++i) {
            int len = rnd.next(1, isCold ? 7 : 5);
            appendRun(a, len, isCold);
            isCold = !isCold;
        }
    }

    if ((int)a.size() > 60) {
        a.resize(60);
    }

    println((int)a.size());
    println(a);

    return 0;
}
