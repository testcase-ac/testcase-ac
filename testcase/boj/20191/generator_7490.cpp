#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Prepare a shuffled pool of lowercase letters
    vector<char> pool;
    for (char c = 'a'; c <= 'z'; ++c) pool.push_back(c);
    shuffle(pool.begin(), pool.end());
    // Decide length of T: sometimes 1, otherwise 2..10
    int L = (rnd.next(0, 9) == 0 ? 1 : rnd.next(2, 10));
    // Alphabet size for T: 1 to min(5, L)
    int k = rnd.next(1, min(5, L));
    vector<char> alph(pool.begin(), pool.begin() + k);
    // Build T by sampling from alph
    string T;
    for (int i = 0; i < L; ++i) {
        T += rnd.any(alph);
    }
    // Decide if the case is solvable or forced impossible
    bool possible = rnd.next(0, 3) != 0; // 75% solvable, 25% impossible
    string S;
    if (!possible) {
        // Impossible: include at least one character not in T
        int sLen = rnd.next(1, 20);
        // Build list of characters not in alph
        vector<char> others;
        for (char c = 'a'; c <= 'z'; ++c) {
            if (find(alph.begin(), alph.end(), c) == alph.end())
                others.push_back(c);
        }
        char bad = rnd.any(others);
        int badPos = rnd.next(0, sLen - 1);
        for (int i = 0; i < sLen; ++i) {
            if (i == badPos) S += bad;
            else S += rnd.any(alph);
        }
    } else {
        // Solvable: generate S as a subsequence of T^n
        int n = rnd.next(1, 5);
        string U;
        for (int i = 0; i < n; ++i) U += T;
        int Ulen = U.size();
        int sLen = rnd.next(1, min(Ulen, 20));
        vector<int> pos(Ulen);
        iota(pos.begin(), pos.end(), 0);
        shuffle(pos.begin(), pos.end());
        pos.resize(sLen);
        sort(pos.begin(), pos.end());
        for (int idx : pos) S += U[idx];
    }
    // Output S then T
    println(S);
    println(T);
    return 0;
}
