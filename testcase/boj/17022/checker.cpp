#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val, prio, sz;
    Node *l, *r;
    Node(int _v, int _p) : val(_v), prio(_p), sz(1), l(nullptr), r(nullptr) {}
};

using pNode = Node*;
std::mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());

int getSize(pNode t) {
    return t ? t->sz : 0;
}

void upd(pNode t) {
    if (t) t->sz = 1 + getSize(t->l) + getSize(t->r);
}

// split t into [0..k-1] -> l, [k..end] -> r
void split(pNode t, int k, pNode &l, pNode &r) {
    if (!t) {
        l = r = nullptr;
    } else if (getSize(t->l) >= k) {
        split(t->l, k, l, t->l);
        r = t;
        upd(r);
    } else {
        split(t->r, k - getSize(t->l) - 1, t->r, r);
        l = t;
        upd(l);
    }
}

pNode merge(pNode a, pNode b) {
    if (!a || !b) return a ? a : b;
    if (a->prio > b->prio) {
        a->r = merge(a->r, b);
        upd(a);
        return a;
    } else {
        b->l = merge(a, b->l);
        upd(b);
        return b;
    }
}

int N;
vector<int> orig;

// reads an answer from stream (ans or ouf), checks validity, simulates it, and returns K
int readAns(InStream &stream) {
    // build initial treap
    pNode root = nullptr;
    for (int i = 0; i < N; i++) {
        pNode nd = new Node(orig[i], (int)rng());
        root = merge(root, nd);
    }
    int K = stream.readInt(0, N, "K");
    for (int i = 0; i < K; i++) {
        int c = stream.readInt(1, N - 1, format("c[%d]", i+1).c_str());
        // take first element
        pNode A, B;
        split(root, 1, A, B);
        // split B into first c and rest
        pNode B1, B2;
        split(B, c, B1, B2);
        // new root = B1 + A + B2
        root = merge(B1, A);
        root = merge(root, B2);
    }
    // check sorted
    // inorder traversal and check a[i] == i+1
    vector<int> stk;
    stk.reserve(N);
    // iterative inorder
    pNode cur = root;
    vector<pNode> s;
    while (cur || !s.empty()) {
        while (cur) {
            s.push_back(cur);
            cur = cur->l;
        }
        cur = s.back(); s.pop_back();
        stk.push_back(cur->val);
        cur = cur->r;
    }
    if ((int)stk.size() != N) {
        stream.quitf(_wa, "internal error: final size %d != %d", (int)stk.size(), N);
    }
    for (int i = 0; i < N; i++) {
        if (stk[i] != i+1) {
            stream.quitf(_wa, "after moves cows are not sorted: at position %d, expected %d, found %d",
                         i+1, i+1, stk[i]);
        }
    }
    return K;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // read input
    N = inf.readInt();
    orig.resize(N);
    for (int i = 0; i < N; i++) {
        orig[i] = inf.readInt();
    }

    int jans = readAns(ans);
    int pans = readAns(ouf);

    if (pans > jans) {
        quitf(_wa, "jury has the better answer: jans = %d, pans = %d", jans, pans);
    } else if (pans == jans) {
        quitf(_ok, "OK: minimum moves = %d", pans);
    } else {
        quitf(_fail, "participant has the better answer than jury: jans = %d, pans = %d", jans, pans);
    }
    return 0;
}
