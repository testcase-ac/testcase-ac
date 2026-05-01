#include "testlib.h"
using namespace std;

string applyOps(const string &s, int mask) {
    int n = (int)s.size();
    string cur = s;
    for (int i = 1; i <= n; i++) {
        if (mask & (1 << (i - 1))) {
            reverse(cur.begin(), cur.begin() + i);
        }
    }
    return cur;
}

string bruteBest(const string &s) {
    int n = (int)s.size();
    int total = 1 << n;
    string best(n, 'Z');
    for (int mask = 0; mask < total; mask++) {
        string t = applyOps(s, mask);
        if (t < best) best = t;
    }
    return best;
}

string generateType2() {
    // Try to find a string whose lexicographically minimal reachable string
    // is NOT just the sorted string.
    for (int tries = 0; tries < 2000; ++tries) {
        int n = rnd.next(4, 10);
        int K = rnd.next(2, 4); // alphabet size
        string s(n, 'A');
        for (int i = 0; i < n; i++) {
            s[i] = char('A' + rnd.next(0, K - 1));
        }

        string sortedS = s;
        sort(sortedS.begin(), sortedS.end());

        string best = bruteBest(s);
        if (best != sortedS) {
            return s;
        }
    }
    // Fallback: simple random if we failed to find such a string
    int n = rnd.next(4, 10);
    int K = rnd.next(2, 4);
    string s(n, 'A');
    for (int i = 0; i < n; i++) s[i] = char('A' + rnd.next(0, K - 1));
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a scenario type to get diverse but still hand-checkable cases.
    int type = rnd.next(0, 5);

    string S;

    if (type == 0) {
        // Type 0: small completely random string
        int n = rnd.next(1, 15);
        int K = rnd.next(1, 5); // alphabet size between 1 and 5
        S.assign(n, 'A');
        for (int i = 0; i < n; i++) {
            S[i] = char('A' + rnd.next(0, K - 1));
        }
    } else if (type == 1) {
        // Type 1: string constructed from a sorted string via valid operations,
        // so the answer is exactly the sorted string.
        int n = rnd.next(5, 20);
        int K = rnd.next(2, 5);
        string sortedS(n, 'A');
        for (int i = 0; i < n; i++) {
            sortedS[i] = char('A' + rnd.next(0, K - 1));
        }
        sort(sortedS.begin(), sortedS.end());
        string cur = sortedS;
        for (int i = 1; i <= n; i++) {
            if (rnd.next(0, 1)) {
                reverse(cur.begin(), cur.begin() + i);
            }
        }
        S = cur;
    } else if (type == 2) {
        // Type 2: brute-force-guaranteed case where the optimal answer
        // is NOT just the globally sorted string.
        S = generateType2();
    } else if (type == 3) {
        // Type 3: palindrome-based strings
        int n = rnd.next(3, 15);
        int K = rnd.next(2, 4);
        S.assign(n, 'A');
        int half = n / 2;
        for (int i = 0; i < half; i++) {
            char c = char('A' + rnd.next(0, K - 1));
            S[i] = c;
            S[n - 1 - i] = c;
        }
        if (n % 2 == 1) {
            S[half] = char('A' + rnd.next(0, K - 1));
        }
    } else if (type == 4) {
        // Type 4: longer random strings (up to ~30)
        int n = rnd.next(20, 30);
        int K = rnd.next(2, 6);
        S.assign(n, 'A');
        for (int i = 0; i < n; i++) {
            S[i] = char('A' + rnd.next(0, K - 1));
        }
    } else if (type == 5) {
        // Type 5: structured patterns (all same, two blocks, alternating)
        int subtype = rnd.next(0, 2);
        if (subtype == 0) {
            // All same character
            int n = rnd.next(5, 20);
            char c = char('A' + rnd.next(0, 5));
            S.assign(n, c);
        } else if (subtype == 1) {
            // Two descending blocks: high letters then low letters
            int n = rnd.next(4, 20);
            int base = rnd.next(0, 20);
            char c1 = char('A' + base);
            char c2 = char('A' + base + rnd.next(1, 5)); // c2 > c1
            int p = rnd.next(1, n - 1);
            S.assign(n, 'A');
            for (int i = 0; i < p; i++) S[i] = c2;
            for (int i = p; i < n; i++) S[i] = c1;
        } else {
            // Alternating pattern ABAB...
            int n = rnd.next(5, 20);
            char a = char('A' + rnd.next(0, 10));
            char b = char('A' + rnd.next(0, 10));
            if (a == b) b = char((b - 'A' + 1) % 26 + 'A');
            S.assign(n, 'A');
            for (int i = 0; i < n; i++) {
                S[i] = (i % 2 == 0 ? a : b);
            }
        }
    }

    println(S);
    return 0;
}
