#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
vector<int> frontToBack;

// Fenwick / BIT for counting inversions
struct BIT {
    int n;
    vector<int> f;
    BIT(int _n = 0) : n(_n), f(n+1, 0) {}
    void add(int i, int v = 1) {
        for (; i <= n; i += i&-i) f[i] += v;
    }
    int sum(int i) {
        int s = 0;
        for (; i > 0; i -= i&-i) s += f[i];
        return s;
    }
};

struct Sol {
    bool no;
    ll invA, invB;
};

Sol readAnsAndCheck(InStream &stream) {
    // Read "Yes"/"No"
    string verdict = stream.readToken();
    if (verdict == "No") {
        // Participant (or jury) says no solution
        return { true, 0, 0 };
    }
    if (verdict != "Yes") {
        stream.quitf(_wa, "expected 'Yes' or 'No', found '%s'", verdict.c_str());
    }
    // Read the two sequences a' and b'
    vector<bool> seen(n+1, false);
    vector<int> A(n), B(n);
    for (int i = 0; i < n; i++) {
        A[i] = stream.readInt(1, n, format("a'[%d]", i+1).c_str());
        if (seen[A[i]]) {
            stream.quitf(_wa, "value %d is reused in the front sequence", A[i]);
        }
        seen[A[i]] = true;
    }
    // reset seen for sanity check (optional)
    // Now read B and check pairing with original deck
    for (int i = 0; i < n; i++) {
        B[i] = stream.readInt(1, n, format("b'[%d]", i+1).c_str());
        int backOrig = frontToBack[A[i]];
        if (B[i] != backOrig) {
            stream.quitf(_wa,
                "b'[%d] = %d does not match original back %d of card with front %d",
                i+1, B[i], backOrig, A[i]);
        }
    }
    // Compute inversion counts of A and B
    ll invA = 0, invB = 0;
    BIT bitA(n), bitB(n);
    for (int i = 0; i < n; i++) {
        // inversions contributed by A[i]
        // # of previous elements > A[i] = i - bitA.sum(A[i])
        invA += (ll)i - bitA.sum(A[i]);
        bitA.add(A[i], 1);
        // same for B
        invB += (ll)i - bitB.sum(B[i]);
        bitB.add(B[i], 1);
    }
    return { false, invA, invB };
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    n = inf.readInt();
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        a[i] = inf.readInt(1, n);
    }
    for (int i = 0; i < n; i++) {
        b[i] = inf.readInt(1, n);
    }
    frontToBack.assign(n+1, 0);
    for (int i = 0; i < n; i++) {
        frontToBack[a[i]] = b[i];
    }
    // Read jury answer and participant answer
    Sol jury = readAnsAndCheck(ans);
    Sol part = readAnsAndCheck(ouf);

    // Compare verdicts
    if (jury.no) {
        if (!part.no) {
            quitf(_wa, "expected 'No'");
        } else {
            quitf(_ok, "correctly answered No");
        }
    } else {
        // jury says Yes
        if (part.no) {
            quitf(_wa, "expected 'Yes'");
        }
        // check that participant's A' and B' have equal inversion counts
        if (part.invA != part.invB) {
            quitf(_wa, "inversion counts differ: inv(a') = %lld, inv(b') = %lld",
                  part.invA, part.invB);
        }
        quitf(_ok, "correct solution with inversion count %lld", part.invA);
    }
    return 0;
}
