#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases [1..10], bias toward smaller
    int T = rnd.wnext(10, -1) + 1;
    println(T);

    const string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int ti = 0; ti < T; ti++) {
        // Original message length [2..12], bias small
        int L = rnd.wnext(10, -2) + 2;
        // Alphabet size for message
        int K = rnd.next(1, min(L, 5));
        // Pick K distinct letters
        vector<char> letters(ALPHA.begin(), ALPHA.end());
        shuffle(letters.begin(), letters.end());
        letters.resize(K);

        // Build original message
        string orig;
        orig.reserve(L);
        for (int i = 0; i < L; i++) {
            orig.push_back(rnd.any(letters));
        }

        // Apply real transformation
        vector<int> cnt(26, 0);
        string M;
        M.reserve(L + L/3 + 2);
        vector<int> ins_pos;
        for (int i = 0; i < (int)orig.size(); i++) {
            char c = orig[i];
            int idx = c - 'A';
            cnt[idx]++;
            M.push_back(c);
            if (cnt[idx] == 3) {
                // insert extra and reset count
                M.push_back(c);
                ins_pos.push_back((int)M.size() - 1);
                cnt[idx] = 0;
            }
        }

        // Decide real or fake (70% real)
        bool make_ok = rnd.next(0, 9) < 7;
        if (make_ok) {
            // Real message
            println(M);
        } else {
            // Fake message by one simple edit
            string fake = M;
            int method = rnd.next(1, 4);
            if (method == 1 && !ins_pos.empty()) {
                // drop an inserted char
                int p = rnd.any(ins_pos);
                if (p < (int)fake.size()) fake.erase(fake.begin() + p);
            }
            else if (method == 2 && !ins_pos.empty()) {
                // change an inserted char to a wrong letter
                int p = rnd.any(ins_pos);
                if (p < (int)fake.size()) {
                    char old = fake[p];
                    string other = ALPHA;
                    other.erase(find(other.begin(), other.end(), old));
                    fake[p] = rnd.any(other);
                }
            }
            else if (method == 3) {
                // add a spurious insertion at a non-insert position
                vector<bool> is_ins(fake.size(), false);
                for (int x : ins_pos) if (x < (int)fake.size()) is_ins[x] = true;
                vector<int> cand;
                for (int i = 0; i < (int)fake.size(); i++)
                    if (!is_ins[i]) cand.push_back(i);
                if (!cand.empty()) {
                    int p = rnd.any(cand);
                    fake.insert(fake.begin() + p, fake[p]);
                } else {
                    // fallback: change a random char
                    int p = rnd.next(0, (int)fake.size() - 1);
                    char old = fake[p];
                    string other = ALPHA;
                    other.erase(find(other.begin(), other.end(), old));
                    fake[p] = rnd.any(other);
                }
            }
            else {
                // drop a random character
                if (!fake.empty()) {
                    int p = rnd.next(0, (int)fake.size() - 1);
                    fake.erase(fake.begin() + p);
                }
            }
            // ensure non-empty
            if (fake.empty()) {
                fake.push_back(rnd.any(letters));
            }
            println(fake);
        }
    }
    return 0;
}
