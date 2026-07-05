#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector<int> identityPermutation(int n) {
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i + 1;
    }
    return p;
}

vector<int> oneCyclePermutation(int n) {
    vector<int> order = identityPermutation(n);
    shuffle(order.begin(), order.end());

    vector<int> p(n + 1);
    for (int i = 0; i < n; ++i) {
        p[order[i]] = order[(i + 1) % n];
    }

    vector<int> result(n);
    for (int i = 1; i <= n; ++i) {
        result[i - 1] = p[i];
    }
    return result;
}

vector<int> swapHeavyPermutation(int n) {
    vector<int> p = identityPermutation(n);
    vector<int> order = identityPermutation(n);
    shuffle(order.begin(), order.end());

    for (int i = 0; i + 1 < n; i += 2) {
        if (rnd.next(0, 3) != 0) {
            swap(p[order[i] - 1], p[order[i + 1] - 1]);
        }
    }
    return p;
}

vector<int> mixedCyclePermutation(int n) {
    vector<int> order = identityPermutation(n);
    shuffle(order.begin(), order.end());

    vector<int> p(n + 1);
    int pos = 0;
    while (pos < n) {
        int remaining = n - pos;
        int len = rnd.next(1, min(remaining, 8));
        if (remaining > 1 && len == remaining - 1) {
            ++len;
        }

        for (int i = 0; i < len; ++i) {
            p[order[pos + i]] = order[pos + (i + 1) % len];
        }
        pos += len;
    }

    vector<int> result(n);
    for (int i = 1; i <= n; ++i) {
        result[i - 1] = p[i];
    }
    return result;
}

string randomEncodedString(int n) {
    const string alphabets = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string symbols = " ?!.,:;_+-=*/0123456789";
    int mode = rnd.next(0, 3);

    string s;
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            s += alphabets[rnd.next((int)alphabets.size())];
        } else if (mode == 1) {
            s += (i % 5 == 0 ? ' ' : alphabets[rnd.next((int)alphabets.size())]);
        } else {
            const string& pool = rnd.next(0, 2) == 0 ? alphabets : symbols;
            s += pool[rnd.next((int)pool.size())];
        }
    }
    if (!s.empty() && s.front() == ' ') {
        s.front() = alphabets[rnd.next((int)alphabets.size())];
    }
    if (!s.empty() && s.back() == ' ') {
        s.back() = alphabets[rnd.next((int)alphabets.size())];
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tc = rnd.next(4, 8);
    for (int caseNo = 0; caseNo < tc; ++caseNo) {
        int n;
        if (caseNo == 0) {
            n = 1;
        } else if (caseNo == 1) {
            n = rnd.next(2, 6);
        } else {
            n = rnd.next(7, 30);
        }

        long long m;
        int mMode = rnd.next(0, 4);
        if (mMode == 0) {
            m = rnd.next(1, 12);
        } else if (mMode == 1) {
            m = rnd.next(13, 1000);
        } else if (mMode == 2) {
            m = 1000000000LL - rnd.next(0, 1000);
        } else {
            m = rnd.next(1, 1000000000);
        }

        vector<int> p;
        int pMode = rnd.next(0, 3);
        if (caseNo == 0 || pMode == 0) {
            p = identityPermutation(n);
        } else if (pMode == 1) {
            p = swapHeavyPermutation(n);
        } else if (pMode == 2) {
            p = oneCyclePermutation(n);
        } else {
            p = mixedCyclePermutation(n);
        }

        println(n, m);
        println(p);
        println(randomEncodedString(n));
    }

    println(0, 0);
    return 0;
}
