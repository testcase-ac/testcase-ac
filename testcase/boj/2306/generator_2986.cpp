#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

// Generate a random KOI gene of exactly 'len' characters (len is even, >=2)
string genKoi(int len) {
    if (len == 2) {
        // Base cases: "at" or "gc"
        return rnd.next(0,1) == 0 ? "at" : "gc";
    }
    // Decide whether to split into concatenation or expand around X
    if (rnd.next(0,1) == 0) {
        // Split into two KOI genes of even lengths l1 and l2 = len-l1
        vector<int> cand;
        for (int l = 2; l <= len-2; l += 2) cand.push_back(l);
        int l1 = rnd.any(cand);
        return genKoi(l1) + genKoi(len - l1);
    } else {
        // Expand: either a X t or g X c
        bool atType = rnd.next(0,1) == 0;
        string inner = genKoi(len - 2);
        return atType ? "a" + inner + "t" : "g" + inner + "c";
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Total length of the DNA sequence
    int n = rnd.next(1, 20);

    // Decide if we output a pure KOI gene (no noise)
    bool wantPure = (n >= 2 && rnd.next() < 0.1);

    int lenK = 0;
    string K;

    if (wantPure) {
        // Pure KOI of random even length up to n
        lenK = 2 * rnd.next(1, n/2);
        K = genKoi(lenK);
        println(K);
        return 0;
    }

    // Otherwise maybe embed a KOI subsequence
    bool wantEmbed = false;
    if (n >= 2 && rnd.next() < 0.8) {
        lenK = 2 * rnd.next(1, n/2);
        K = genKoi(lenK);
        wantEmbed = true;
    }

    // Build the noisy DNA string
    vector<char> letters = {'a','c','g','t'};
    string S(n, ' ');
    for (int i = 0; i < n; i++) {
        S[i] = rnd.any(letters);
    }

    // Embed the KOI subsequence as a subsequence if desired
    if (wantEmbed) {
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        shuffle(idx.begin(), idx.end());
        sort(idx.begin(), idx.begin() + lenK);
        for (int i = 0; i < lenK; i++) {
            S[idx[i]] = K[i];
        }
    }

    // Output the single DNA sequence
    println(S);
    return 0;
}
