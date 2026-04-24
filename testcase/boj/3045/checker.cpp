#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<int> prevM, nextM;

// Apply one operation of type op ('A' or 'B') moving node X before/after Y,
// on the given prev/next arrays.
void apply_op(char op, int X, int Y, vector<int>& prev, vector<int>& next) {
    // remove X
    int p = prev[X], n = next[X];
    if (p != 0) next[p] = n;
    if (n != 0) prev[n] = p;
    // insert
    if (op == 'A') {
        // before Y
        int pY = prev[Y];
        prev[X] = pY;
        next[X] = Y;
        prev[Y] = X;
        if (pY != 0) next[pY] = X;
    } else {
        // after Y
        int nY = next[Y];
        prev[X] = Y;
        next[X] = nY;
        next[Y] = X;
        if (nY != 0) prev[nY] = X;
    }
}

// Reads and checks an answer from stream; returns K (number of ops).
// Uses the state after the input M operations as the starting point, stored in prevM/nextM.
int readAns(InStream &stream) {
    // copy the state after input-ops
    vector<int> prev = prevM, next = nextM;
    // read K
    int K = stream.readInt(0, N + M, "number of operations");
    for (int i = 1; i <= K; i++) {
        string tok = stream.readToken("operation");
        if (tok.size() != 1 || (tok[0] != 'A' && tok[0] != 'B')) {
            stream.quitf(_wa, "operation #%d: expected 'A' or 'B', found '%s'", i, tok.c_str());
        }
        char op = tok[0];
        int X = stream.readInt(1, N, format("X in operation #%d", i).c_str());
        int Y = stream.readInt(1, N, format("Y in operation #%d", i).c_str());
        if (X == Y) {
            stream.quitf(_wa, "operation #%d: X and Y must differ, both are %d", i, X);
        }
        // apply
        apply_op(op, X, Y, prev, next);
    }
    // After applying all, check we are back to initial list 1..N
    // find head
    int head = 0;
    for (int i = 1; i <= N; i++) {
        if (prev[i] == 0) {
            head = i;
            break;
        }
    }
    if (head != 1) {
        stream.quitf(_wa, "head of list is %d, expected 1", head);
    }
    // traverse and check sequence
    int cur = head;
    for (int exp = 1; exp <= N; exp++) {
        if (cur == 0) {
            stream.quitf(_wa, "list ended prematurely at position %d, expected %d", exp, exp);
        }
        if (cur != exp) {
            stream.quitf(_wa, "at position %d found node %d, expected %d", exp, cur, exp);
        }
        cur = next[cur];
    }
    if (cur != 0) {
        stream.quitf(_wa, "list has extra nodes beyond position %d", N);
    }
    return K;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // read input
    N = inf.readInt();
    M = inf.readInt();
    // build initial list
    prevM.assign(N+1, 0);
    nextM.assign(N+1, 0);
    for (int i = 1; i < N; i++) {
        nextM[i] = i+1;
        prevM[i+1] = i;
    }
    // apply the M operations from input
    for (int i = 0; i < M; i++) {
        char op = inf.readToken()[0];
        int X = inf.readInt(1, N);
        int Y = inf.readInt(1, N);
        apply_op(op, X, Y, prevM, nextM);
    }
    // read and check jury and participant answers
    int jans = readAns(ans);
    int pans = readAns(ouf);
    if (pans > jans) {
        quitf(_wa, "participant uses more operations than minimal: jury = %d, participant = %d", jans, pans);
    } else if (pans < jans) {
        quitf(_fail, "participant uses fewer operations than jury: jury = %d, participant = %d", jans, pans);
    } else {
        quitf(_ok, "optimal number of operations = %d", pans);
    }
    return 0;
}
