#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N and M sizes
    int tN = rnd.next(-1, 1);
    int N = max(1, rnd.wnext(12, tN));
    int tM = rnd.next(-1, 1);
    int M = max(1, rnd.wnext(12, tM));
    int K = rnd.next(1, N);

    // Define a small alphabet subset to pick sticker letters from
    int alph = rnd.next(1, min(26, M));
    vector<char> baseLetters;
    for (int i = 0; i < alph; ++i) baseLetters.push_back(char('a' + i));

    // Assign sticker types s_j
    vector<char> s(M);
    for (int j = 0; j < M; ++j) {
        s[j] = rnd.any(baseLetters);
    }
    // Collect actual letters present in stickers
    vector<char> sj_letters;
    for (char c : s) {
        if (find(sj_letters.begin(), sj_letters.end(), c) == sj_letters.end())
            sj_letters.push_back(c);
    }

    // Decide if we force an impossible case
    bool impossible = rnd.next(0, 4) == 0;
    // Build outside letters (not in sj_letters) for impossible scenario
    vector<char> outside;
    for (char c = 'a'; c <= 'z'; ++c) {
        if (find(sj_letters.begin(), sj_letters.end(), c) == sj_letters.end())
            outside.push_back(c);
    }

    // Generate target string S
    string S(K, 'a');
    if (!impossible) {
        // Always pick from available sticker letters
        for (int i = 0; i < K; ++i)
            S[i] = rnd.any(sj_letters);
    } else {
        // First build from available, then inject one impossible character
        for (int i = 0; i < K; ++i)
            S[i] = rnd.any(sj_letters);
        if (!outside.empty()) {
            int pos = rnd.next(0, K - 1);
            S[pos] = rnd.any(outside);
        }
    }

    // Initial board stickers b_i
    vector<int> b(N);
    for (int i = 0; i < N; ++i)
        b[i] = rnd.next(1, M);

    // Costs a_j (purchase) and d_j (removal) with variability
    vector<int> a(M), d(M);
    for (int j = 0; j < M; ++j) {
        if (rnd.next(0, 1) == 0) {
            // removal cheap, purchase expensive
            d[j] = rnd.next(1, 20);
            a[j] = rnd.next(20, 100);
        } else {
            // purchase cheap, removal expensive
            a[j] = rnd.next(1, 20);
            d[j] = rnd.next(20, 100);
        }
    }

    // Output
    println(N, M, K);
    for (int j = 0; j < M; ++j) {
        printf("%c %d %d\n", s[j], d[j], a[j]);
    }
    println(b);
    printf("%s\n", S.c_str());

    return 0;
}
