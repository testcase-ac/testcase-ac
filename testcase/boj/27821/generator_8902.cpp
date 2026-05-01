#include "testlib.h"
using namespace std;

string toHexFixed(int x, int D) {
    string s(D, '0');
    for (int i = D - 1; i >= 0; --i) {
        int d = x & 15;
        s[i] = (d < 10 ? char('0' + d) : char('A' + (d - 10)));
        x >>= 4;
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        // Choose D with a bias toward smaller sizes
        int modeD = rnd.next(0, 9);
        int D;
        if (modeD <= 3) D = 2;
        else if (modeD <= 6) D = 3;
        else if (modeD <= 8) D = 4;
        else D = 5;

        int maxVal = 1;
        for (int i = 0; i < D; ++i) maxVal *= 16;

        // Choose range [S, E]
        int rangeMode = rnd.next(0, 4);
        int sVal = 0, eVal = maxVal - 1;
        if (rangeMode == 0) {
            // Full range
            sVal = 0;
            eVal = maxVal - 1;
        } else if (rangeMode == 1) {
            // Single point
            sVal = rnd.next(0, maxVal - 1);
            eVal = sVal;
        } else if (rangeMode == 2) {
            // Prefix from 0
            eVal = rnd.next(0, maxVal - 1);
            sVal = 0;
        } else if (rangeMode == 3) {
            // Suffix to max
            sVal = rnd.next(0, maxVal - 1);
            eVal = maxVal - 1;
        } else {
            // Small internal window
            sVal = rnd.next(0, maxVal - 1);
            int maxLen = maxVal - 1 - sVal;
            if (maxLen > 32) maxLen = 32;
            int len = rnd.next(0, maxLen);
            eVal = sVal + len;
        }

        string S = toHexFixed(sVal, D);
        string E = toHexFixed(eVal, D);

        // Choose N with small sizes
        int NUpper = min(10, 3 * D);
        if (NUpper < 2) NUpper = 2;
        int N = rnd.next(2, NUpper);

        vector<string> L;
        L.reserve(N);

        int listMode = rnd.next(0, 5);
        if (listMode == 0) {
            // All identical
            int baseVal = rnd.next(0, maxVal - 1);
            string baseStr = toHexFixed(baseVal, D);
            for (int i = 0; i < N; ++i) L.push_back(baseStr);
        } else if (listMode == 1) {
            // Two values mixed, creating duplicates
            int aVal = rnd.next(0, maxVal - 1);
            int bVal = rnd.next(0, maxVal - 1);
            if (bVal == aVal) bVal = (bVal + 1) % maxVal;
            string aStr = toHexFixed(aVal, D);
            string bStr = toHexFixed(bVal, D);
            for (int i = 0; i < N; ++i) {
                if (rnd.next(0, 1) == 0) L.push_back(aStr);
                else L.push_back(bStr);
            }
        } else if (listMode == 2) {
            // Arithmetic progression modulo 16^D
            int start = rnd.next(0, maxVal - 1);
            int step = rnd.next(1, maxVal - 1);
            for (int i = 0; i < N; ++i) {
                int v = (start + (int)(1LL * i * step % maxVal)) % maxVal;
                L.push_back(toHexFixed(v, D));
            }
        } else if (listMode == 3) {
            // Random numbers built from a small digit subset
            string alph = "0123456789ABCDEF";
            int k = rnd.next(2, 5);
            vector<char> cand;
            while ((int)cand.size() < k) {
                char c = alph[rnd.next(0, 15)];
                bool used = false;
                for (char x : cand) if (x == c) { used = true; break; }
                if (!used) cand.push_back(c);
            }
            for (int i = 0; i < N; ++i) {
                string cur;
                cur.reserve(D);
                for (int j = 0; j < D; ++j) {
                    char c = rnd.any(cand);
                    cur.push_back(c);
                }
                L.push_back(cur);
            }
        } else if (listMode == 4) {
            // Fully random values
            for (int i = 0; i < N; ++i) {
                int v = rnd.next(0, maxVal - 1);
                L.push_back(toHexFixed(v, D));
            }
        } else {
            // Values clustered around S and E, explicitly including S and E
            if (N >= 1) L.push_back(S);
            if (N >= 2) L.push_back(E);
            while ((int)L.size() < N) {
                int choice = rnd.next(0, 1);
                int base = (choice == 0 ? sVal : eVal);
                int delta = rnd.next(0, 6) - 3; // -3..3
                int v = base + delta;
                if (v < 0) v += maxVal;
                if (v >= maxVal) v -= maxVal;
                L.push_back(toHexFixed(v, D));
            }
        }

        shuffle(L.begin(), L.end());

        println(N, D);
        println(S, E);
        println(L);
    }

    return 0;
}
