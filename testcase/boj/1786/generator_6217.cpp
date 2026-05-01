#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Text length n and pattern length m
    int n = rnd.next(1, 30);
    int m = rnd.next(1, n);

    // Allowed characters: letters and space
    string chars = "abcdefghijklmnopqrstuvwxyz"
                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    string letters = "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Generate pattern P with variety: random, periodic, homogeneous
    string P;
    int ptype = rnd.next(0, 2);
    if (ptype == 0 || m < 2) {
        // fully random
        for (int i = 0; i < m; i++)
            P += rnd.any(chars);
    } else if (ptype == 1) {
        // periodic pattern
        int k = rnd.next(1, m - 1);
        string base;
        for (int i = 0; i < k; i++)
            base += rnd.any(chars);
        for (int i = 0; i < m; i++)
            P += base[i % k];
    } else {
        // homogeneous pattern
        char c = rnd.any(chars);
        P = string(m, c);
    }
    // Ensure P contains at least one non-space to avoid blank-line issues
    bool hasNonSpaceP = false;
    for (char c : P) if (c != ' ') { hasNonSpaceP = true; break; }
    if (!hasNonSpaceP) {
        int pos = rnd.next(0, m - 1);
        P[pos] = rnd.any(letters);
    }

    // Generate text T
    string T;
    T.reserve(n);
    for (int i = 0; i < n; i++)
        T += rnd.any(chars);

    // Ensure T contains at least one non-space
    bool hasNonSpaceT = false;
    for (char c : T) if (c != ' ') { hasNonSpaceT = true; break; }
    if (!hasNonSpaceT) {
        int pos = rnd.next(0, n - 1);
        T[pos] = rnd.any(letters);
    }

    // Embed P into T: 0 times, once, or multiple times
    int embed = rnd.next(0, 2);
    if (embed == 1) {
        // single embed
        int pos = rnd.next(0, n - m);
        for (int i = 0; i < m; i++)
            T[pos + i] = P[i];
    } else if (embed == 2 && n - m + 1 >= 2) {
        // multiple embeddings, allow overlaps, up to 4 places
        int maxc = min(n - m + 1, 4);
        int cnt = rnd.next(2, maxc);
        for (int t = 0; t < cnt; t++) {
            int pos = rnd.next(0, n - m);
            for (int i = 0; i < m; i++)
                T[pos + i] = P[i];
        }
    }
    // Output
    println(T);
    println(P);
    return 0;
}
