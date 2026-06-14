#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

long long chooseWeight(int mode, int i, int j) {
    if (mode == 0) {
        return 1;
    }
    if (mode == 1) {
        return (i == j ? 1000000000LL : 1);
    }
    if (mode == 2) {
        return 1 + 1LL * (i + 1) * (j + 1);
    }
    if (mode == 3) {
        return (i + j) % 3 == 0 ? 1000000000LL : rnd.next(1, 1000);
    }
    if (mode == 4) {
        return rnd.next(1, 20);
    }
    return rnd.next(1, 1000000000);
}

vector<int> makeTypes(int len, int c, int mode) {
    vector<int> v(len);
    if (mode == 0) {
        int x = rnd.next(1, c);
        fill(v.begin(), v.end(), x);
    } else if (mode == 1) {
        for (int i = 0; i < len; ++i) {
            v[i] = i % c + 1;
        }
    } else if (mode == 2) {
        for (int i = 0; i < len; ++i) {
            v[i] = c - (i % c);
        }
    } else if (mode == 3) {
        int x = rnd.next(1, c);
        int y = rnd.next(1, c);
        for (int i = 0; i < len; ++i) {
            v[i] = (i % 2 == 0 ? x : y);
        }
    } else {
        for (int i = 0; i < len; ++i) {
            v[i] = rnd.next(1, c);
        }
    }
    if (len > 1 && rnd.next(0, 3) == 0) {
        shuffle(v.begin(), v.end());
    }
    return v;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int c;
    int n;
    int m;

    if (mode == 0) {
        c = 2;
        n = 1;
        m = 1;
    } else if (mode == 1) {
        c = rnd.next(2, 4);
        n = rnd.next(1, 5);
        m = rnd.next(1, 5);
    } else if (mode == 2) {
        c = rnd.next(2, 6);
        n = rnd.next(8, 18);
        m = rnd.next(1, 4);
    } else if (mode == 3) {
        c = rnd.next(2, 6);
        n = rnd.next(1, 4);
        m = rnd.next(8, 18);
    } else if (mode == 4) {
        c = rnd.next(8, 16);
        n = rnd.next(10, 28);
        m = rnd.next(10, 28);
    } else if (mode == 5) {
        c = 16;
        n = rnd.next(20, 45);
        m = rnd.next(20, 45);
    } else {
        c = rnd.next(2, 16);
        n = rnd.next(2, 35);
        m = rnd.next(2, 35);
    }

    int weightMode = rnd.next(0, 5);
    vector<vector<long long>> w(c, vector<long long>(c));
    for (int i = 0; i < c; ++i) {
        for (int j = i; j < c; ++j) {
            w[i][j] = w[j][i] = chooseWeight(weightMode, i, j);
        }
    }

    vector<int> a = makeTypes(n, c, rnd.next(0, 4));
    vector<int> b = makeTypes(m, c, rnd.next(0, 4));

    println(n, m, c);
    for (int i = 0; i < c; ++i) {
        println(w[i]);
    }
    println(a);
    println(b);

    return 0;
}
