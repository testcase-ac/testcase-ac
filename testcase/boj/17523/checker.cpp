#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int m, n;
long long r;
vector<long long> P;
vector<int> S, E;

// readAns reads a solution from stream (ans or ouf), checks its validity,
// and returns the number of steps (or -1). On invalidity it quits with
// _wa if stream==ouf or _fail if stream==ans.
int readAns(InStream &stream) {
    // read number of steps, can be -1
    int maxSteps = n * m;
    int MIN = stream.readInt(-1, maxSteps, "number of steps");
    if (MIN == -1) {
        // no moves
        return MIN;
    }
    // initialize current occupied intervals
    set<pair<long long,int>> currPos;
    for (int s : S) {
        currPos.insert({P[s-1], s});
    }
    // process moves
    for (int i = 0; i < MIN; i++) {
        int a = stream.readInt(1, n, format("move[%d].from", i+1).c_str());
        int b = stream.readInt(1, n, format("move[%d].to", i+1).c_str());
        // a must be occupied
        auto itA = currPos.find({P[a-1], a});
        if (itA == currPos.end()) {
            stream.quitf(_wa, "in move %d, interval %d is not occupied", i+1, a);
        }
        // b must be free
        if (currPos.count({P[b-1], b})) {
            stream.quitf(_wa, "in move %d, interval %d is already occupied", i+1, b);
        }
        // a and b must intersect: [P[a-1], P[a-1]+r] intersects [P[b-1], P[b-1]+r]
        if (!(P[b-1] <= P[a-1] + r && P[a-1] <= P[b-1] + r)) {
            stream.quitf(_wa, "in move %d, intervals %d and %d do not intersect", i+1, a, b);
        }
        // b must not intersect any other occupied c != a
        long long lb = P[b-1] - r;
        long long ub = P[b-1] + r;
        // find first with P[c] >= lb
        auto it = currPos.lower_bound({max(lb, 0LL), -2000000000});
        for (; it != currPos.end() && it->first <= ub; ++it) {
            int c = it->second;
            if (c == a) continue;
            // c intersects b
            stream.quitf(_wa, "in move %d, interval %d intersects interval %d", i+1, b, c);
        }
        // perform move
        currPos.erase(itA);
        currPos.insert({P[b-1], b});
    }
    // after all moves, check final configuration equals E
    if ((int)currPos.size() != m) {
        stream.quitf(_wa, "final number of occupied intervals is %d, expected %d",
                    (int)currPos.size(), m);
    }
    vector<int> finalOcc;
    finalOcc.reserve(m);
    for (auto &pr : currPos)
        finalOcc.push_back(pr.second);
    if (finalOcc != E) {
        stream.quitf(_wa, "final configuration differs from expected");
    }
    return MIN;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    // read input
    m = inf.readInt();
    n = inf.readInt();
    r = inf.readInt();
    P.resize(n);
    for (int i = 0; i < n; i++) {
        P[i] = inf.readInt();
    }
    S.resize(m);
    for (int i = 0; i < m; i++) {
        S[i] = inf.readInt();
    }
    E.resize(m);
    for (int i = 0; i < m; i++) {
        E[i] = inf.readInt();
    }
    // read jury and participant answers
    int jans = readAns(ans);
    int pans = readAns(ouf);
    // compare
    if (jans == -1 && pans == -1) {
        quitf(_ok, "both answers are -1");
    }
    if (jans == -1 && pans != -1) {
        quitf(_wa, "expected -1, found %d", pans);
    }
    if (jans != -1 && pans == -1) {
        quitf(_wa, "found -1, expected %d", jans);
    }
    // both non-negative
    if (pans != jans) {
        quitf(_wa, "expected %d moves, found %d", jans, pans);
    }
    quitf(_ok, "%d moves", pans);
    return 0;
}
