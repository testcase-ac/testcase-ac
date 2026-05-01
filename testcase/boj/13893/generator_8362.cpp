#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

bool startsWith(const string &s, const string &p) {
    return s.size() >= p.size() && s.rfind(p, 0) == 0;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 4);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Generate initial dictionary size N
        int N = rnd.wnext(9, 1) + 1;  // 1 to 10, bias larger
        set<string> used;
        vector<string> dict;

        // Create up to 2 prefix-sharing groups
        int groups = rnd.next(0, 2);
        int rem = N;
        for (int g = 0; g < groups && rem >= 2; g++) {
            int gsize = rnd.next(2, min(rem, 4));
            rem -= gsize;
            int pLen = rnd.next(1, 3);
            string pref;
            for (int i = 0; i < pLen; i++)
                pref += char('a' + rnd.next(0, 25));
            for (int i = 0; i < gsize; i++) {
                int sufLen = rnd.next(1, 3);
                string w = pref;
                for (int j = 0; j < sufLen; j++)
                    w += char('a' + rnd.next(0, 25));
                if (used.insert(w).second)
                    dict.push_back(w);
                else i--; // retry
            }
        }
        // Fill the rest with random unique words
        while ((int)dict.size() < N) {
            int L = rnd.next(1, 6);
            string w;
            for (int i = 0; i < L; i++)
                w += char('a' + rnd.next(0, 25));
            if (used.insert(w).second)
                dict.push_back(w);
        }

        // Output initial dictionary
        println(N);
        for (auto &w : dict) println(w);

        // Generate queries
        int Q = rnd.wnext(9, -1) + 1; // 1 to 10, bias smaller
        println(Q);
        set<string> qUsed;
        for (int qi = 0; qi < Q; qi++) {
            string q;
            int typ = rnd.next(1, 3);
            if (typ == 1 && !dict.empty()) {
                // prefix of an existing word
                string base = rnd.any(dict);
                int l = rnd.next(1, (int)base.size());
                q = base.substr(0, l);
            } else if (typ == 2) {
                // completely new, not prefix of any
                for (int it = 0; it < 100; it++) {
                    int L = rnd.next(1, 5);
                    string cand;
                    for (int i = 0; i < L; i++)
                        cand += char('a' + rnd.next(0, 25));
                    bool ok = used.count(cand) == 0;
                    for (auto &d : dict) {
                        if (startsWith(d, cand)) { ok = false; break; }
                    }
                    if (ok) { q = cand; break; }
                }
                if (q.empty()) { // fallback
                    q = "z";
                }
            } else {
                // extend a prefix of existing
                if (dict.empty()) {
                    q = "a";
                } else {
                    string base = rnd.any(dict);
                    int l = rnd.next(1, (int)base.size());
                    string pref = base.substr(0, l);
                    int sufLen = rnd.next(1, 3);
                    q = pref;
                    for (int i = 0; i < sufLen; i++)
                        q += char('a' + rnd.next(0, 25));
                }
            }
            // avoid duplicate queries
            if (qUsed.count(q)) { qi--; continue; }
            qUsed.insert(q);
            println(q);
            // add to dictionary
            if (used.insert(q).second)
                dict.push_back(q);
        }
    }
    return 0;
}
