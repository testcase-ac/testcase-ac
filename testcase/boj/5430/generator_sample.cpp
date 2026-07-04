#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string makeProgram(int n, int mode) {
    string p;
    if (mode == 0) {
        int len = rnd.next(1, 8);
        for (int i = 0; i < len; ++i) p.push_back(rnd.any(string("RD")));
    } else if (mode == 1) {
        int drops = n + rnd.next(1, 4);
        for (int i = 0; i < drops; ++i) {
            if (rnd.next(0, 2) == 0) p.push_back('R');
            p.push_back('D');
        }
    } else if (mode == 2) {
        int pairs = rnd.next(1, 6);
        for (int i = 0; i < pairs; ++i) p += "RR";
        int drops = rnd.next(0, n);
        for (int i = 0; i < drops; ++i) p.push_back('D');
        if (p.empty()) p = "R";
    } else {
        int drops = rnd.next(0, n);
        for (int i = 0; i < drops; ++i) {
            if (rnd.next(0, 3) == 0) p.push_back('R');
            p.push_back('D');
        }
        int tail = rnd.next(1, 6);
        for (int i = 0; i < tail; ++i) p.push_back(rnd.any(string("RRD")));
    }
    return p;
}

vector<int> makeArray(int n, int mode) {
    vector<int> values;
    values.reserve(n);

    if (mode == 0) {
        int value = rnd.next(1, 100);
        values.assign(n, value);
    } else if (mode == 1) {
        int start = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) values.push_back(1 + (start + i - 1) % 100);
    } else if (mode == 2) {
        int start = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) values.push_back(1 + (start + n - i - 1) % 100);
    } else {
        int lo = rnd.next(1, 90);
        int hi = rnd.next(lo, 100);
        for (int i = 0; i < n; ++i) values.push_back(rnd.next(lo, hi));
    }

    return values;
}

void printArray(const vector<int>& values) {
    printf("[");
    for (int i = 0; i < (int)values.size(); ++i) {
        if (i > 0) printf(",");
        printf("%d", values[i]);
    }
    printf("]\n");
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 8);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int nMode = rnd.next(0, 5);
        int n = 0;
        if (nMode == 0) {
            n = 0;
        } else if (nMode == 1) {
            n = 1;
        } else {
            n = rnd.next(2, 15);
        }

        int programMode = rnd.next(0, 3);
        string p = makeProgram(n, programMode);
        vector<int> values = makeArray(n, rnd.next(0, 3));

        println(p);
        println(n);
        printArray(values);
    }

    return 0;
}
