#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int maxN = 10;
    // Decide if we generate a valid or invalid case
    bool valid = rnd.next(0,1) == 1;
    int N;
    string S;
    vector<int> cnt(4, 0), avail(4, 0);
    if (valid) {
        // Valid cases
        int sub = rnd.next(0,2);
        if (sub == 0) {
            // N = 1, single 'a'
            N = 1;
            S = "a";
        } else {
            // N >= 3
            N = rnd.next(3, maxN);
            S = string(N, ' ');
            S[0] = 'a';
            S[N-1] = 'a';
            // fill middle with b/c/d avoiding adjacency and avoiding 'a' at N-2
            for (int i = 1; i <= N-2; i++) {
                char prev = S[i-1];
                vector<char> cand = {'b','c','d'};
                cand.erase(remove(cand.begin(), cand.end(), prev), cand.end());
                // if at the last middle pos (i == N-2), also avoid 'a' but we only pick from bcd
                S[i] = rnd.any(cand);
            }
        }
        // count used
        for (char c : S) cnt[c - 'a']++;
        // set avail >= used, add small slack
        for (int i = 0; i < 4; i++) {
            avail[i] = cnt[i] + rnd.next(0,2);
        }
    } else {
        // Invalid cases
        int type = rnd.next(0,2);
        if (type == 0) {
            // Invalid because ends not 'a'
            N = rnd.next(1, maxN);
            S.clear();
            for (int i = 0; i < N; i++) {
                // pick from b/c/d only
                S.push_back(rnd.any(string("bcd")));
                cnt[S.back()-'a']++;
            }
            // set avail >= used
            // ensure sum>=1 automatically since used>=1
            for (int i = 0; i < 4; i++) {
                if (i == 0) {
                    avail[i] = rnd.next(0,2);
                } else {
                    avail[i] = cnt[i] + rnd.next(0,1);
                }
            }
        } else if (type == 1) {
            // Invalid because adjacent duplicate
            N = rnd.next(2, maxN);
            S = string(N, ' ');
            S[0] = 'a';
            S[N-1] = 'a';
            if (N > 2) {
                for (int i = 1; i <= N-2; i++) {
                    char prev = S[i-1];
                    vector<char> cand = {'b','c','d'};
                    cand.erase(remove(cand.begin(), cand.end(), prev), cand.end());
                    S[i] = rnd.any(cand);
                }
            }
            // inject an adjacent duplicate
            int pos = rnd.next(0, N-2);
            S[pos+1] = S[pos];
            for (char c : S) cnt[c-'a']++;
            // set avail >= used
            for (int i = 0; i < 4; i++) {
                avail[i] = cnt[i] + rnd.next(0,2);
            }
        } else {
            // Invalid because exceed availability for some letter
            // build a valid string first
            N = rnd.next(3, maxN);
            S = string(N, ' ');
            S[0] = 'a';
            S[N-1] = 'a';
            for (int i = 1; i <= N-2; i++) {
                char prev = S[i-1];
                vector<char> cand = {'b','c','d'};
                cand.erase(remove(cand.begin(), cand.end(), prev), cand.end());
                S[i] = rnd.any(cand);
            }
            for (char c : S) cnt[c-'a']++;
            // pick a letter that appears to under-allocate
            vector<int> usedLetters;
            for (int i = 0; i < 4; i++) if (cnt[i] > 0) usedLetters.push_back(i);
            int bad = rnd.any(usedLetters);
            // for the bad letter, avail < cnt
            avail[bad] = cnt[bad] - rnd.next(1, cnt[bad]);
            // for others, avail >= cnt
            for (int i = 0; i < 4; i++) if (i != bad) {
                avail[i] = cnt[i] + rnd.next(0,1);
            }
        }
    }
    // Output the test case
    println(N);
    println(avail[0], avail[1], avail[2], avail[3]);
    println(S);
    return 0;
}
