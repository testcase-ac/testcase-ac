#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters
    int K = rnd.next(1, 7);               // Number of sets
    double noiseProb = rnd.next();        // Probability to insert noise after a token

    // Noise words cannot be any set's first token: se, mik-jjang, Are, u-, hai
    vector<string> noiseWords = {
        "hello","wow","hey","test","random","noise","something",
        "boo","la","kappa","foo","bar","baz"
    };

    vector<string> outputWords;

    auto maybeNoise = [&]() {
        if (rnd.next() < noiseProb) {
            // pick one noise word
            string w = rnd.any(noiseWords);
            outputWords.push_back(w);
        }
    };

    for (int i = 0; i < K; i++) {
        int t = rnd.next(0, 4);
        if (t == 0) {
            // A set: se no hai- hai- hai hai hai hai (u- hai)*n
            vector<string> baseA = {
                "se","no","hai-","hai-","hai","hai","hai","hai"
            };
            for (auto &w : baseA) {
                outputWords.push_back(w);
                maybeNoise();
            }
            int n = rnd.next(1, 5);
            for (int j = 0; j < n; j++) {
                outputWords.push_back("u-");
                maybeNoise();
                outputWords.push_back("hai");
                maybeNoise();
            }
        } else if (t == 1) {
            // B set: mik-jjang kawaii!
            vector<string> baseB = {"mik-jjang", "kawaii!"};
            for (auto &w : baseB) {
                outputWords.push_back(w);
                maybeNoise();
            }
        } else if (t == 2) {
            // C set: Are you ready antena senku high!
            vector<string> baseC = {"Are","you","ready","antena","senku","high!"};
            for (auto &w : baseC) {
                outputWords.push_back(w);
                maybeNoise();
            }
        } else if (t == 3) {
            // D set: u- hai
            outputWords.push_back("u-");
            maybeNoise();
            outputWords.push_back("hai");
            maybeNoise();
        } else {
            // E set: hai
            outputWords.push_back("hai");
            maybeNoise();
        }
    }

    // Join into single line
    string S;
    for (int i = 0; i < (int)outputWords.size(); i++) {
        if (i) S += ' ';
        S += outputWords[i];
    }
    println(S);

    return 0;
}
