#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Length of the street
    int N = rnd.next(1, 10);
    // Alphabet size for diversity
    int K = rnd.next(2, 4);
    string alph;
    for (int i = 0; i < K; i++) alph.push_back(char('a' + i));

    // Generate the street string
    string s;
    for (int i = 0; i < N; i++) {
        s.push_back(rnd.any(alph));
    }

    // Number of tile bundles
    int M = rnd.next(1, 5);
    vector<string> tiles;
    for (int i = 0; i < M; i++) {
        int type = rnd.next(0, 3);
        string t;
        if (type == 0) {
            // exact substring from s
            int l = rnd.next(0, N - 1);
            int r = rnd.next(l, N - 1);
            t = s.substr(l, r - l + 1);
        } else if (type == 1) {
            // substring with one character modified
            int l = rnd.next(0, N - 1);
            int r = rnd.next(l, N - 1);
            t = s.substr(l, r - l + 1);
            int pos = rnd.next(0, int(t.size()) - 1);
            char nc;
            do { nc = rnd.any(alph); } while (nc == t[pos]);
            t[pos] = nc;
        } else if (type == 2) {
            // random string of length up to N
            int len = rnd.next(1, N);
            for (int j = 0; j < len; j++) t.push_back(rnd.any(alph));
        } else {
            // random string longer than N to ensure no full match
            int len = rnd.next(N + 1, N + 5);
            for (int j = 0; j < len; j++) t.push_back(rnd.any(alph));
        }
        tiles.push_back(t);
    }

    // Shuffle tile bundles to randomize order
    shuffle(tiles.begin(), tiles.end());

    // Output in required format
    println(N);
    printf("%s\n", s.c_str());
    println(M);
    for (auto &t : tiles) {
        printf("%s\n", t.c_str());
    }

    return 0;
}
