#include "testlib.h"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

string genWord(int len) {
    string s;
    for (int i = 0; i < len; i++) {
        s.push_back(char('A' + rnd.next(0, 25)));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.wnext(5, rnd.next(-1, 1));  // bias toward extremes
    T = max(1, T);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Choose n
        int n = rnd.wnext(10, rnd.next(-1, 1));
        n = max(1, n);
        // Generate first public key: n distinct words
        set<string> used;
        vector<string> K1;
        while ((int)K1.size() < n) {
            // word length distribution: mix short and long
            int len;
            double p = rnd.next();
            if (p < 0.4) len = rnd.next(1, 3);
            else if (p < 0.8) len = rnd.next(4, 7);
            else len = rnd.next(8, 10);
            string w = genWord(len);
            if (!used.count(w)) {
                used.insert(w);
                K1.push_back(w);
            }
        }
        // Permutation for second key
        vector<int> perm(n);
        for (int i = 0; i < n; i++) perm[i] = i;
        shuffle(perm.begin(), perm.end());
        // Build second public key
        vector<string> K2(n);
        for (int i = 0; i < n; i++) {
            K2[perm[i]] = K1[i];
        }
        // Generate plaintext of length n (allow repeats)
        vector<string> P(n);
        for (int i = 0; i < n; i++) {
            P[i] = rnd.any(K1);
        }
        // Build ciphertext by inverse perm: C[perm[i]] = P[i]
        vector<string> C(n);
        for (int i = 0; i < n; i++) {
            C[perm[i]] = P[i];
        }
        // Output this test case
        println(n);
        println(K1);
        println(K2);
        println(C);
    }
    return 0;
}
