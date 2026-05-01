#include "testlib.h"
using namespace std;

int minPeriod(const string &t) {
    int L = (int)t.size();
    for (int d = 1; d <= L; ++d) {
        if (L % d != 0) continue;
        bool ok = true;
        for (int i = d; i < L && ok; ++i) {
            if (t[i] != t[i % d]) ok = false;
        }
        if (ok) return d;
    }
    return L;
}

string randomString(int len, char maxC) {
    string s(len, 'A');
    int range = maxC - 'A';
    for (int i = 0; i < len; ++i) {
        s[i] = char('A' + rnd.next(0, range));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    vector<string> S;
    int K;

    int scenario = rnd.next(0, 6); // 7 scenarios: 0..6

    if (scenario == 0) {
        // Small N, small alphabet
        N = rnd.next(1, 4);
        S.resize(N);
        int totalLen = 0;
        char maxC = char('A' + rnd.next(0, 2)); // 'A'..'C'
        for (int i = 0; i < N; ++i) {
            int len = rnd.next(1, 10);
            S[i] = randomString(len, maxC);
            totalLen += len;
        }
        int L = totalLen;
        if (rnd.next(0, 1) == 0 && L >= 1) {
            K = rnd.next(1, min(L, 200));
        } else {
            K = rnd.next(1, 200);
        }
    } else if (scenario == 1) {
        // Fully random within constraints
        N = rnd.next(1, 8);
        S.resize(N);
        int totalLen = 0;
        for (int i = 0; i < N; ++i) {
            int len = rnd.next(1, 20);
            S[i] = randomString(len, 'Z');
            totalLen += len;
        }
        int L = totalLen;
        if (rnd.next(0, 2) == 0 && L >= 1) {
            K = rnd.next(1, min(L, 200));
        } else {
            K = rnd.next(1, 200);
        }
    } else if (scenario == 2) {
        // All strings equal: all 'A's, tests factorial counting
        N = rnd.next(2, 8);
        int len = rnd.next(1, 20);
        S.assign(N, string(len, 'A'));
        int L = N * len;
        if (rnd.next(0, 1) == 0) {
            // Every permutation is magic
            K = min(L, 200);
        } else {
            // Likely 0 permutations magic
            do {
                K = rnd.next(1, 200);
            } while (K == L);
        }
    } else if (scenario == 3) {
        // Few base words, many duplicates
        int baseCnt = rnd.next(1, 3);
        vector<string> base;
        for (int i = 0; i < baseCnt; ++i) {
            int len = rnd.next(1, 10);
            base.push_back(randomString(len, 'D')); // small alphabet
        }
        N = rnd.next(baseCnt, 8);
        S.resize(N);
        int totalLen = 0;
        for (int i = 0; i < N; ++i) {
            S[i] = rnd.any(base);
            totalLen += (int)S[i].size();
        }
        int L = totalLen;
        if (rnd.next(0, 1) == 0 && L >= 1) {
            K = rnd.next(1, min(L, 200));
        } else {
            K = rnd.next(1, 200);
        }
    } else if (scenario == 4) {
        // Construct a globally periodic concatenation T that is magic for at least one permutation
        N = rnd.next(2, 8);
        int minL = N;
        int maxL = N * 20;
        int L = rnd.next(minL, maxL);

        // Choose a period length d dividing L
        vector<int> divs;
        for (int d = 1; d <= L; ++d)
            if (L % d == 0) divs.push_back(d);
        int d = rnd.any(divs);

        // Build T from repeating a random pattern of length d
        string pattern = randomString(d, 'D');
        string T;
        T.reserve(L);
        int reps = L / d;
        for (int i = 0; i < reps; ++i) T += pattern;

        // Compute real minimal period & K
        int d2 = minPeriod(T);
        int Ktrue = L / d2;

        // Cut T into N pieces, each length in [1,20]
        vector<int> lens(N, 1);
        int rem = L - N;
        for (int i = 0; i < N; ++i) {
            int can = min(19, rem);
            int add = (i == N - 1 ? can : rnd.next(0, can));
            lens[i] += add;
            rem -= add;
        }
        // Now build S from T
        S.resize(N);
        int pos = 0;
        for (int i = 0; i < N; ++i) {
            S[i] = T.substr(pos, lens[i]);
            pos += lens[i];
        }

        // Choose K sometimes equal to Ktrue, sometimes not
        if (rnd.next(0, 2) <= 1) {
            K = min(Ktrue, 200);
            if (K == 0) K = 1;
        } else {
            do {
                K = rnd.next(1, 200);
            } while (K == Ktrue);
        }
    } else if (scenario == 5) {
        // Many 'A's and one slightly different word
        N = rnd.next(3, 8);
        int len = rnd.next(2, 20);
        S.clear();
        for (int i = 0; i < N - 1; ++i) {
            S.push_back(string(len, 'A'));
        }
        string last(len, 'A');
        int pos = rnd.next(0, len - 1);
        last[pos] = 'B';
        S.push_back(last);

        int L = N * len;
        vector<int> candidates;
        candidates.push_back(1);
        candidates.push_back(min(L, 200));
        candidates.push_back(rnd.next(1, 200));
        K = rnd.any(candidates);
    } else {
        // scenario == 6: Max N, varied lengths, mixed letters
        N = 8;
        S.resize(N);
        int totalLen = 0;
        for (int i = 0; i < N; ++i) {
            int len = rnd.next(1, 20);
            char maxC = (rnd.next(0, 1) == 0 ? 'C' : 'Z');
            S[i] = randomString(len, maxC);
            totalLen += len;
        }
        int L = totalLen;
        // Bias K sometimes to divisor/length-like values
        int choice = rnd.next(0, 2);
        if (choice == 0 && L >= 1) {
            K = rnd.next(1, min(L, 200));
        } else {
            K = rnd.next(1, 200);
        }
    }

    // Output
    println(N);
    for (int i = 0; i < N; ++i) {
        println(S[i]);
    }
    println(K);

    return 0;
}
