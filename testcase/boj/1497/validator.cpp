#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 10, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    vector<string> names(N);
    vector<string> plays(N);
    set<string> usedNames;

    for (int i = 0; i < N; ++i) {
        // name: uppercase letters, length 2..50
        names[i] = inf.readToken("[A-Z]{2,50}", "guitar_name");
        inf.readSpace();
        // play string: exactly M chars of 'Y' or 'N'
        plays[i] = inf.readToken("[YN]{1,50}", "play_info");
        inf.readEoln();

        ensuref((int)plays[i].size() == M,
                "Line %d: play_info length mismatch, expected %d, got %d",
                i + 2, M, (int)plays[i].size());

        ensuref(!usedNames.count(names[i]),
                "Duplicate guitar name at line %d: %s", i + 2, names[i].c_str());
        usedNames.insert(names[i]);
    }

    // Compute the globally maximum number of songs that can be played
    // by any subset of guitars, and check that the output described
    // in the problem is always well-defined (at least one song playable
    // or not).
    // The problem guarantees that the optimal number of playable songs
    // is the maximum union size over subsets; this is inherent in the
    // formulation, so here we just compute the maximum number of
    // playable songs, to later allow generators to enforce constraints
    // if needed (no extra constraints given in statement though).
    //
    // Also, we can check that M <= 50, N <= 10, so using bitsets
    // and subset enumeration is safe.

    int maxSongs = 0;
    // Encode each guitar's play string as a bitmask over M songs.
    vector<unsigned long long> mask(N, 0ULL);
    // M <= 50, fits in 64-bit
    for (int i = 0; i < N; ++i) {
        unsigned long long m = 0;
        for (int j = 0; j < M; ++j) {
            if (plays[i][j] == 'Y') {
                m |= (1ULL << j);
            }
        }
        mask[i] = m;
    }

    int totalSubsets = 1 << N;
    for (int s = 1; s < totalSubsets; ++s) {
        unsigned long long u = 0;
        for (int i = 0; i < N; ++i) {
            if (s & (1 << i)) u |= mask[i];
        }
        int cnt = __builtin_popcountll(u);
        if (cnt > maxSongs) maxSongs = cnt;
    }
    // maxSongs is the maximum number of playable songs over all subsets.
    // The statement only uses this value conceptually ("최대한 많은 곡"),
    // but does not impose any additional global constraints like
    // "answer always at least 1", so we do not enforce anything here.

    inf.readEof();
}
