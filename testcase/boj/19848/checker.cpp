#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Implicit treap to maintain a sequence of '0'/'1' with range checks.
struct Node {
    char c;
    int pr, sz;
    Node *l, *r;
    // segment info
    bool all_eq;
    char lc, rc;  // leftmost char, rightmost char
    int pre, suf; // length of equal-char prefix and suffix
    Node(char _c): c(_c), pr(rnd.next()), sz(1),
        l(nullptr), r(nullptr),
        all_eq(true), lc(_c), rc(_c),
        pre(1), suf(1) {}
};

int sz(Node* t) { return t ? t->sz : 0; }

void upd(Node* t) {
    if (!t) return;
    t->sz = 1 + sz(t->l) + sz(t->r);
    t->lc = t->l ? t->l->lc : t->c;
    t->rc = t->r ? t->r->rc : t->c;
    t->all_eq = true;
    if (t->l && !t->l->all_eq) t->all_eq = false;
    if (t->r && !t->r->all_eq) t->all_eq = false;
    if (t->l && t->l->rc != t->c) t->all_eq = false;
    if (t->r && t->r->lc != t->c) t->all_eq = false;
    // prefix
    t->pre = (t->l ? t->l->pre : 0);
    if (t->pre == sz(t->l) && ( !t->l || t->l->rc == t->c )) {
        t->pre += 1;
        if (t->r && t->r->lc == t->c)
            t->pre += t->r->pre;
    }
    // suffix
    t->suf = (t->r ? t->r->suf : 0);
    if (t->suf == sz(t->r) && ( !t->r || t->r->lc == t->c )) {
        t->suf += 1;
        if (t->l && t->l->rc == t->c)
            t->suf += t->l->suf;
    }
}

void split(Node* t, Node*& l, Node*& r, int k) {
    // left gets first k elements, right the rest
    if (!t) { l = r = nullptr; return; }
    if (sz(t->l) >= k) {
        split(t->l, l, t->l, k);
        r = t;
    } else {
        split(t->r, t->r, r, k - sz(t->l) - 1);
        l = t;
    }
    upd(t);
}

Node* merge(Node* a, Node* b) {
    if (!a || !b) return a ? a : b;
    if (a->pr > b->pr) {
        a->r = merge(a->r, b);
        upd(a);
        return a;
    } else {
        b->l = merge(a, b->l);
        upd(b);
        return b;
    }
}

// read and apply answer from 'stream' on the treap 't'
// returns K = number of operations, or -1 if impossible
int readAns(InStream &stream, Node* &t) {
    // read K, allow -1
    if (stream.eof())
        stream.quitf(&stream == &ans ? _fail : _wa,
                     "unexpected eof while reading K");
    int K = stream.readInt();
    if (K == -1) {
        // no more lines
        return -1;
    }
    if (K < 0 || K > sz(t) / 2)
        stream.quitf(&stream == &ans ? _fail : _wa,
                     "invalid number of operations: %d", K);
    for (int i = 1; i <= K; i++) {
        if (t == nullptr)
            stream.quitf(&stream == &ans ? _fail : _wa,
                         "string already empty before op %d", i);
        int n = sz(t);
        int b = stream.readInt(1, n, format("b_%d", i).c_str());
        int e = stream.readInt(1, n, format("e_%d", i).c_str());
        if (b > e)
            stream.quitf(&stream == &ans ? _fail : _wa,
                         "b_%d > e_%d (%d > %d)", i, i, b, e);
        int len = e - b + 1;
        if (len % 2 != 0)
            stream.quitf(&stream == &ans ? _fail : _wa,
                         "length of removed substring at op %d is not even: %d", i, len);
        int k = len / 2;
        // split into [0..b-2], [b-1..e-1], [e..]
        Node *t1, *t2, *tmid, *t3;
        split(t, t1, t2, b - 1);
        split(t2, tmid, t3, len);
        if (!tmid || sz(tmid) != len)
            stream.quitf(&stream == &ans ? _fail : _wa,
                         "split error at op %d", i);
        // check prefix/suffix
        if (tmid->pre < k)
            stream.quitf(&stream == &ans ? _fail : _wa,
                         "first half not all equal at op %d: need %d, have %d",
                         i, k, tmid->pre);
        if (tmid->suf < k)
            stream.quitf(&stream == &ans ? _fail : _wa,
                         "second half not all equal at op %d: need %d, have %d",
                         i, k, tmid->suf);
        if (tmid->lc == tmid->rc)
            stream.quitf(&stream == &ans ? _fail : _wa,
                         "substring must contain both '0' and '1' at op %d", i);
        // remove the middle
        t = merge(t1, t3);
    }
    if (t && sz(t) != 0)
        stream.quitf(&stream == &ans ? _fail : _wa,
                     "string not empty after all %d operations, still length %d",
                     K, sz(t));
    return K;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    string S = inf.readToken();
    int n = (int)S.size();
    // build two treaps, one for jury, one for participant
    Node *tj = nullptr, *tp = nullptr;
    for (char c : S) {
        if (c!='0' && c!='1') quitf(_fail, "invalid input char");
        tj = merge(tj, new Node(c));
        tp = merge(tp, new Node(c));
    }

    // read jury and participant answers
    int Kj = readAns(ans, tj);
    int Kp = readAns(ouf, tp);

    // compare
    if (Kj == -1 && Kp == -1) {
        quitf(_ok, "both say -1 (impossible)");
    }
    if (Kj == -1 && Kp != -1) {
        quitf(_wa, "participant found a solution but jury says impossible");
    }
    if (Kj != -1 && Kp == -1) {
        quitf(_wa, "participant says impossible but jury has solution of %d ops", Kj);
    }
    // both >= 0
    if (Kj > Kp) {
        quitf(_fail, "participant used fewer ops (%d) than jury's minimal (%d)", Kp, Kj);
    }
    if (Kj < Kp) {
        quitf(_wa, "participant used more ops (%d) than minimal (%d)", Kp, Kj);
    }
    // equal
    quitf(_ok, "correct, %d operations", Kp);
    return 0;
}
