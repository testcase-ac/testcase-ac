#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string alternating(int n, char first) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back((i % 2 == 0) ? first : (first == 'I' ? 'O' : 'I'));
    }
    return s;
}

string randomString(int n, int iPercent) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(rnd.next(1, 100) <= iPercent ? 'I' : 'O');
    }
    return s;
}

string runString(int n, int maxRun, char first) {
    string s;
    char c = first;
    while ((int)s.size() < n) {
        int len = min(rnd.next(1, maxRun), n - (int)s.size());
        s.append(len, c);
        c = (c == 'I' ? 'O' : 'I');
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 30);
    int m = rnd.next(1, 30);
    string s, t;

    if (mode == 0) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 8);
        s.assign(n, rnd.next(0, 1) ? 'I' : 'O');
        t.assign(m, rnd.next(0, 1) ? 'I' : 'O');
    } else if (mode == 1) {
        s = alternating(n, rnd.next(0, 1) ? 'I' : 'O');
        t = alternating(m, rnd.next(0, 1) ? 'I' : 'O');
    } else if (mode == 2) {
        int iPercent = rnd.any(vector<int>{10, 25, 50, 75, 90});
        s = randomString(n, iPercent);
        t = randomString(m, 100 - iPercent);
    } else if (mode == 3) {
        int maxRun = rnd.next(2, 6);
        s = runString(n, maxRun, rnd.next(0, 1) ? 'I' : 'O');
        t = runString(m, maxRun, rnd.next(0, 1) ? 'I' : 'O');
    } else if (mode == 4) {
        n = rnd.next(10, 45);
        m = rnd.next(10, 45);
        s = randomString(n, rnd.next(35, 65));
        t = randomString(m, rnd.next(35, 65));
    } else if (mode == 5) {
        n = rnd.next(1, 12);
        m = rnd.next(1, 12);
        int skipS = rnd.next(0, n - 1);
        int skipT = rnd.next(0, m - 1);
        s = string(skipS, 'O') + alternating(n - skipS, 'I');
        t = string(skipT, 'O') + alternating(m - skipT, 'I');
    } else {
        n = rnd.next(1, 3);
        m = rnd.next(1, 30);
        s = randomString(n, rnd.next(0, 100));
        t = runString(m, rnd.next(1, 4), rnd.next(0, 1) ? 'I' : 'O');
    }

    n = (int)s.size();
    m = (int)t.size();
    println(n, m);
    println(s);
    println(t);

    return 0;
}
