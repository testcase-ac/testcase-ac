#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N and M with some edges
    int N = rnd.next(1, 12);
    int M;
    int edgeM = rnd.next(100);
    if (edgeM < 20) M = 1;
    else if (edgeM < 40) M = 12;
    else M = rnd.next(1, 12);

    // Choose K with some edge bias: sometimes 1 or N
    int K;
    int edgeK = rnd.next(100);
    if (edgeK < 20) K = 1;
    else if (edgeK < 40) K = N;
    else K = rnd.next(1, N);

    // Alphabet size skewed small for diversity
    int alpha = rnd.wnext(26, -3) + 1; // in [1,26], skew toward small
    vector<char> letters(alpha);
    for (int i = 0; i < alpha; i++) letters[i] = char('A' + i);

    vector<string> S(N);
    for (int i = 0; i < N; i++) {
        // Occasionally repeat a previous string to create duplicates
        if (i > 0 && rnd.next(100) < 15) {
            S[i] = rnd.any(vector<string>(S.begin(), S.begin() + i));
            continue;
        }
        // Pick a form: 0 random, 1 sorted, 2 reverse sorted, 3 repeated char
        int form = rnd.next(0, 3);
        string t;
        if (form == 3) {
            char c = rnd.any(letters);
            t = string(M, c);
        } else {
            t.resize(M);
            for (int j = 0; j < M; j++) t[j] = rnd.any(letters);
            if (form == 1) sort(t.begin(), t.end());
            else if (form == 2) sort(t.begin(), t.end(), greater<char>());
        }
        S[i] = t;
    }

    // Shuffle order of strings slightly
    shuffle(S.begin(), S.end());

    // Output
    println(N, M, K);
    for (auto &s : S) println(s);
    return 0;
}
