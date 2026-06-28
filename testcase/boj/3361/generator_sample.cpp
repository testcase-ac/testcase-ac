#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 40);
    string s;

    if (mode == 0) {
        s.assign(n, rnd.next(0, 1) == 0 ? 'L' : 'R');
    } else if (mode == 1) {
        int leftCount = rnd.next(0, n);
        s.assign(leftCount, 'L');
        s.append(n - leftCount, 'R');
    } else if (mode == 2) {
        int rightCount = rnd.next(0, n);
        s.assign(rightCount, 'R');
        s.append(n - rightCount, 'L');
    } else if (mode == 3) {
        char first = rnd.next(0, 1) == 0 ? 'L' : 'R';
        for (int i = 0; i < n; ++i) {
            s.push_back((i % 2 == 0) == (first == 'L') ? 'L' : 'R');
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            s.push_back(rnd.next(0, 99) < 70 ? 'R' : 'L');
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            s.push_back(rnd.next(0, 99) < 70 ? 'L' : 'R');
        }
    } else if (mode == 6) {
        int prefix = rnd.next(0, n);
        int suffix = rnd.next(0, n - prefix);
        int middle = n - prefix - suffix;
        s.assign(prefix, 'L');
        for (int i = 0; i < middle; ++i) {
            s.push_back(rnd.next(0, 1) == 0 ? 'L' : 'R');
        }
        s.append(suffix, 'R');
    } else {
        while ((int)s.size() < n) {
            char c = rnd.next(0, 1) == 0 ? 'L' : 'R';
            int runLength = rnd.next(1, 8);
            s.append(min(runLength, n - (int)s.size()), c);
        }
    }

    println(s);
    return 0;
}
