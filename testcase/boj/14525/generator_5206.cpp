#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N = rnd.next(1, 8);           // number of cows per type
    int M = rnd.next(3, 20);          // genome length

    // Choose a random subset of the alphabet {A,C,G,T}
    string fullAlpha = "ACGT";
    shuffle(fullAlpha.begin(), fullAlpha.end());
    int K = rnd.next(2, 4);           // use between 2 and 4 letters
    string alpha = fullAlpha.substr(0, K);

    // Generate spotty genomes
    vector<string> spot(N);
    set<string> spotSet;
    for (int i = 0; i < N; i++) {
        string s;
        s.reserve(M);
        for (int j = 0; j < M; j++) {
            s.push_back(rnd.any(alpha));
        }
        spot[i] = s;
        spotSet.insert(s);
    }

    // Generate plain genomes, ensuring no full-string collision with spotty
    vector<string> plain(N);
    for (int i = 0; i < N; i++) {
        string s;
        do {
            s.clear();
            for (int j = 0; j < M; j++) {
                s.push_back(rnd.any(alpha));
            }
        } while (spotSet.count(s));
        plain[i] = s;
    }

    // Output
    println(N, M);
    for (auto &s : spot) println(s);
    for (auto &s : plain) println(s);

    return 0;
}
