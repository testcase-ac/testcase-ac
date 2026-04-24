#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N = rnd.next(1, 10);         // number of words
    int K = rnd.next(1, 10);         // syllable target per line
    int M = rnd.next(1, 10);         // number of lines in poem
    int C = rnd.next(1, N);          // number of rhyme classes

    // Generate words with random syllables and classes
    vector<int> s(N), c(N);
    for (int i = 0; i < N; i++) {
        s[i] = rnd.next(1, K);
        c[i] = rnd.next(1, C);
    }

    // Rhyme scheme: choose D distinct letters, then assign to M lines
    int D = rnd.next(1, min(M, 3));
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    shuffle(alpha.begin(), alpha.end());
    vector<char> distinct;
    for (int i = 0; i < D; i++) distinct.push_back(alpha[i]);

    vector<char> scheme;
    // ensure each letter appears at least once
    for (int i = 0; i < D; i++) scheme.push_back(distinct[i]);
    // fill the rest
    for (int i = D; i < M; i++) scheme.push_back(rnd.any(distinct));
    shuffle(scheme.begin(), scheme.end());

    // Output
    println(N, M, K);
    for (int i = 0; i < N; i++) {
        println(s[i], c[i]);
    }
    for (char ch : scheme) {
        printf("%c\n", ch);
    }
    return 0;
}
