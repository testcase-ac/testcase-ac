#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose small to medium N
    int N = rnd.next(1, 12);

    // Decide tree shape
    int treeType = rnd.next(0, 3);
    vector<pair<int,int>> edges;
    if (N > 1) {
        if (treeType == 0) {
            // Chain
            for (int i = 1; i < N; i++)
                edges.emplace_back(i, i+1);
        } else if (treeType == 1) {
            // Star
            int center = rnd.next(1, N);
            for (int i = 1; i <= N; i++)
                if (i != center)
                    edges.emplace_back(center, i);
        } else if (treeType == 2) {
            // Random parent < i
            for (int i = 2; i <= N; i++) {
                int p = rnd.next(1, i-1);
                edges.emplace_back(p, i);
            }
        } else {
            // Balanced-ish binary tree
            for (int i = 2; i <= N; i++) {
                int p = i/2;
                if (p < 1) p = 1;
                edges.emplace_back(p, i);
            }
        }
        // Shuffle edge order
        shuffle(edges.begin(), edges.end());
    }

    // Decide fruit pattern
    int pat = rnd.next(0, 3);
    string s(N, 'A');
    if (pat == 0) {
        // all A
        // s is already 'A's
    } else if (pat == 1) {
        // all B
        for (int i = 0; i < N; i++) s[i] = 'B';
    } else if (pat == 2) {
        // exactly half (or as close as possible)
        int cntA = N/2;
        if (cntA == 0) cntA = 1;
        vector<char> v(N, 'B');
        for (int i = 0; i < cntA; i++) v[i] = 'A';
        shuffle(v.begin(), v.end());
        for (int i = 0; i < N; i++) s[i] = v[i];
    } else {
        // skewed random
        for (int i = 0; i < N; i++)
            s[i] = (rnd.next(0, 9) < 3 ? 'A' : 'B');
        // ensure both types appear if possible
        bool hasA = false, hasB = false;
        for (char c : s) {
            if (c == 'A') hasA = true;
            if (c == 'B') hasB = true;
        }
        if (!hasA && N > 0) s[rnd.next(0, N-1)] = 'A';
        if (!hasB && N > 0) s[rnd.next(0, N-1)] = 'B';
    }

    // Output
    println(N);
    printf("%s\n", s.c_str());
    for (auto &e : edges) println(e.first, e.second);

    return 0;
}
