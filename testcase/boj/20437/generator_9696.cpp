#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<string, int>> tests;

    // 1) All same character, random length and K
    {
        int n = rnd.next(1, 20);
        char c = char('a' + rnd.next(0, 25));
        string w(n, c);
        int k = rnd.next(1, n);
        tests.push_back({w, k});
    }

    // 2) All distinct characters (shuffled), guaranteed -1 (K >= 2)
    {
        int n = rnd.next(5, 26);
        string base = "abcdefghijklmnopqrstuvwxyz";
        string w = base.substr(0, n);
        shuffle(w.begin(), w.end());
        int k = rnd.next(2, n); // all characters appear once -> no solution
        tests.push_back({w, k});
    }

    // 3) Fixed example-like tricky case
    {
        string w = "abaaaba";
        int k = 3;
        tests.push_back({w, k});
    }

    // 4) Two-letter string with sometimes solution, sometimes -1
    {
        int n = rnd.next(5, 25);
        char c1 = char('a' + rnd.next(0, 25));
        char c2;
        do {
            c2 = char('a' + rnd.next(0, 25));
        } while (c2 == c1);

        string w(n, c1);
        int f1 = 0, f2 = 0;
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1) == 0) {
                w[i] = c1;
                ++f1;
            } else {
                w[i] = c2;
                ++f2;
            }
        }
        int maxfreq = max(f1, f2);
        int k;
        bool wantSolution = (rnd.next(0, 1) == 0);
        if (wantSolution || maxfreq == n) {
            // Ensure at least one character appears >= K times
            if (maxfreq == 0) {
                // degenerate, but can't happen since n>=5
                k = 1;
            } else {
                k = rnd.next(1, maxfreq);
            }
        } else {
            // Force no solution: choose K > maxfreq if possible
            if (maxfreq < n) {
                k = rnd.next(maxfreq + 1, n);
            } else {
                // fallback, should not really happen
                k = rnd.next(1, maxfreq);
            }
        }
        tests.push_back({w, k});
    }

    // 5) Random 2-5 letter alphabet, guaranteed solution
    {
        int n = rnd.next(5, 30);
        int alpha = rnd.next(2, 5);
        string w(n, 'a');
        vector<int> freq(26, 0);
        for (int i = 0; i < n; ++i) {
            char c = char('a' + rnd.next(0, alpha - 1));
            w[i] = c;
            freq[c - 'a']++;
        }
        // pick a character that actually appears
        vector<int> present;
        for (int i = 0; i < alpha; ++i)
            if (freq[i] > 0) present.push_back(i);
        int idx = rnd.any(present);
        int k = rnd.next(1, freq[idx]);
        tests.push_back({w, k});
    }

    // 6) Medium string with one heavy character
    {
        int n = rnd.next(20, 30);
        char mainc = char('a' + rnd.next(0, 25));
        vector<char> others;
        for (char ch = 'a'; ch <= 'z'; ++ch)
            if (ch != mainc) others.push_back(ch);

        int freqMain = rnd.next(2, n); // at least 2
        string w(n, mainc);
        for (int i = freqMain; i < n; ++i) {
            w[i] = rnd.any(others);
        }
        shuffle(w.begin(), w.end());

        int k = rnd.next(2, min(freqMain, 10)); // small-ish K, at least 2
        tests.push_back({w, k});
    }

    // 7) K = |W|, but string not all the same -> guaranteed -1
    {
        int n = rnd.next(2, 10);
        char c1 = char('a' + rnd.next(0, 25));
        char c2;
        do {
            c2 = char('a' + rnd.next(0, 25));
        } while (c2 == c1);

        string w(n, c1);
        for (int i = 1; i < n; ++i) {
            w[i] = (rnd.next(0, 1) == 0 ? c1 : c2);
        }
        w[1] = c2; // ensure at least one different character
        int k = n; // no character appears n times
        tests.push_back({w, k});
    }

    // 8) Very small string (length 1-3), random K with/without solution
    {
        int n = rnd.next(1, 3);
        string w(n, 'a');
        vector<int> freq(26, 0);
        for (int i = 0; i < n; ++i) {
            char c = char('a' + rnd.next(0, 2)); // 'a'..'c' for readability
            w[i] = c;
            freq[c - 'a']++;
        }
        int maxf = 0;
        for (int f : freq) maxf = max(maxf, f);
        int k;
        if (rnd.next(0, 1) == 0 && maxf > 0) {
            // ensure solution
            k = rnd.next(1, maxf);
        } else if (maxf < n) {
            // possible to have no solution
            k = rnd.next(maxf + 1, n);
        } else {
            // all same character, any 1..n yields solution
            k = rnd.next(1, n);
        }
        tests.push_back({w, k});
    }

    // Shuffle test cases to avoid fixed ordering patterns
    shuffle(tests.begin(), tests.end());

    int T = (int)tests.size();
    println(T);
    for (auto &tc : tests) {
        println(tc.first);
        println(tc.second);
    }

    return 0;
}
