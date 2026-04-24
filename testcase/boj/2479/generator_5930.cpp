#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
struct Entry {
    string code;
    bool markStart = false;
    bool markEnd = false;
};
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameters
    int K = rnd.next(2, 10);
    int maxN = min((int)(1 << K), 10);
    int N = rnd.next(3, maxN);
    bool ensurePath = rnd.next(0, 1);

    vector<string> codes;
    unordered_set<string> used;
    int idxA = -1, idxB = -1;

    if (ensurePath) {
        // build a path of length L
        int L = rnd.next(2, N);
        // generate first code
        string cur(K, '0');
        for (int i = 0; i < K; i++)
            cur[i] = rnd.next(0,1) ? '1' : '0';
        used.insert(cur);
        codes.push_back(cur);
        // extend path
        for (int step = 1; step < L; step++) {
            string prev = codes.back();
            // try flipping bits in random order
            vector<int> bits(K);
            iota(bits.begin(), bits.end(), 0);
            shuffle(bits.begin(), bits.end());
            string next = prev;
            bool found = false;
            for (int b : bits) {
                next = prev;
                next[b] = (prev[b] == '0' ? '1' : '0');
                if (!used.count(next)) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                // shouldn't happen, fallback to random fresh code
                do {
                    next = "";
                    for (int i = 0; i < K; i++)
                        next += rnd.next(0,1) ? '1' : '0';
                } while (used.count(next));
            }
            used.insert(next);
            codes.push_back(next);
        }
        // assign A and B in the path
        idxA = 0;
        idxB = (int)codes.size() - 1;
        // fill remaining random codes
        while ((int)codes.size() < N) {
            string s;
            do {
                s.clear();
                for (int i = 0; i < K; i++)
                    s += rnd.next(0,1) ? '1' : '0';
            } while (used.count(s));
            used.insert(s);
            codes.push_back(s);
        }
    } else {
        // entirely random codes
        while ((int)codes.size() < N) {
            string s;
            do {
                s.clear();
                for (int i = 0; i < K; i++)
                    s += rnd.next(0,1) ? '1' : '0';
            } while (used.count(s));
            used.insert(s);
            codes.push_back(s);
        }
        idxA = rnd.next(0, N-1);
        do {
            idxB = rnd.next(0, N-1);
        } while (idxB == idxA);
    }

    // prepare entries and marks
    vector<Entry> entries;
    entries.reserve(N);
    for (int i = 0; i < N; i++) {
        Entry e;
        e.code = codes[i];
        e.markStart = (i == idxA);
        e.markEnd = (i == idxB);
        entries.push_back(e);
    }
    // shuffle to randomize positions
    shuffle(entries.begin(), entries.end());

    // find final indices
    int A = -1, B = -1;
    for (int i = 0; i < N; i++) {
        if (entries[i].markStart) A = i+1;
        if (entries[i].markEnd) B = i+1;
    }

    // output
    println(N, K);
    for (auto &e : entries) println(e.code);
    println(A, B);
    return 0;
}
