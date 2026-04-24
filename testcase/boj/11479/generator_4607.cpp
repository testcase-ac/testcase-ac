#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // length of string
    int N = rnd.next(1, 10);

    // choose alphabet size
    int K = rnd.next(1, min(26, N));
    string letters = "abcdefghijklmnopqrstuvwxyz";
    shuffle(letters.begin(), letters.end());
    letters.resize(K);

    string S;
    S.reserve(N);

    // two modes: random or periodic repetition
    int mode = rnd.next(0, 1);
    if (mode == 0) {
        // purely random string
        for (int i = 0; i < N; i++) {
            S.push_back(rnd.any(letters));
        }
    } else {
        // periodic repetition of a random block
        int Lb = rnd.next(1, N);
        string block;
        block.reserve(Lb);
        for (int i = 0; i < Lb; i++) {
            block.push_back(rnd.any(letters));
        }
        for (int i = 0; i < N; i++) {
            S.push_back(block[i % Lb]);
        }
    }

    // occasionally add a palindromic tail
    if (N >= 3 && rnd.next(0, 1) == 0) {
        int t = rnd.next(1, N/2);
        for (int i = 0; i < t; i++) {
            S[N - 1 - i] = S[i];
        }
    }

    // output the generated string
    printf("%s\n", S.c_str());
    return 0;
}
