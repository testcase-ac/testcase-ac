#include "testlib.h"
#include <string>
#include <vector>
#include <set>
#include <array>
#include <algorithm>
using namespace std;

bool isSimilar(const string &a, const string &b) {
    array<int,26> ca = {0}, cb = {0};
    for (char ch : a) ca[ch-'A']++;
    for (char ch : b) cb[ch-'A']++;
    if (ca == cb) return true;
    int diff = 0;
    for (int i = 0; i < 26; i++) diff += abs(ca[i] - cb[i]);
    if (diff == 1) return true;           // insertion or deletion
    if (diff == 2 && a.size() == b.size()) return true; // substitution
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 10);
    // Generate base word
    int L = rnd.next(1, 10);
    string base;
    for (int i = 0; i < L; i++)
        base += char(rnd.next('A', 'Z'));

    double simProb = rnd.next(0.0, 1.0);
    set<string> seen;
    vector<string> words;
    seen.insert(base);
    words.push_back(base);

    while ((int)words.size() < n) {
        bool makeSim = rnd.next() < simProb;
        string w;
        if (makeSim) {
            // pick a similarity operation
            vector<int> types = {0,3}; // 0=perm,3=subst
            if ((int)base.size() < 10) types.push_back(1);
            if ((int)base.size() > 1) types.push_back(2);
            int t = rnd.any(types);
            w = base;
            if (t == 0) {
                shuffle(w.begin(), w.end());
            } else if (t == 1) {
                int pos = rnd.next(0, (int)w.size());
                w.insert(w.begin() + pos, char(rnd.next('A','Z')));
            } else if (t == 2) {
                int pos = rnd.next(0, (int)w.size() - 1);
                w.erase(w.begin() + pos);
            } else {
                int pos = rnd.next(0, (int)w.size() - 1);
                char c;
                do { c = char(rnd.next('A','Z')); } while (c == w[pos]);
                w[pos] = c;
            }
        } else {
            // generate random until not similar or max tries
            int tries = 0;
            do {
                int L2 = rnd.next(1, 10);
                w.clear();
                for (int i = 0; i < L2; i++)
                    w += char(rnd.next('A', 'Z'));
                tries++;
            } while (tries < 50 && isSimilar(w, base));
        }
        if (seen.insert(w).second) {
            words.push_back(w);
        }
    }

    // Output
    println(n);
    for (auto &s : words)
        println(s);

    return 0;
}
