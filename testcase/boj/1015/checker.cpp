#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;

vector<int> readAnswer(InStream& stream) {
    vector<int> p(n);
    vector<int> seen(n, 0);

    for (int i = 0; i < n; ++i) {
        p[i] = stream.readInt(0, n - 1, format("p[%d]", i).c_str());
        if (seen[p[i]]) {
            stream.quitf(_wa, "p[%d]=%d is duplicated", i, p[i]);
        }
        seen[p[i]] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after permutation");
    }

    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        b[p[i]] = a[i];
    }
    for (int i = 1; i < n; ++i) {
        if (b[i - 1] > b[i]) {
            stream.quitf(_wa,
                         "applied sequence is not nondecreasing at b[%d]=%d and b[%d]=%d",
                         i - 1,
                         b[i - 1],
                         i,
                         b[i]);
        }
    }

    return p;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    a = inf.readInts(n);

    vector<int> jury = readAnswer(ans);
    vector<int> participant = readAnswer(ouf);

    if (participant < jury) {
        quitf(_fail, "participant output is lexicographically smaller than jury output");
    }
    if (participant != jury) {
        quitf(_wa, "expected lexicographically smallest permutation");
    }

    quitf(_ok, "valid lexicographically smallest permutation");
}
