#include "testlib.h"
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 500, "N");
    inf.readSpace();
    int M = inf.readInt(3, 500, "M");
    inf.readEoln();

    // Read spotty cow genomes
    vector<string> spot(N);
    for (int i = 0; i < N; i++) {
        spot[i] = inf.readToken("[ACGT]+", "spot_seq");
        // Ensure exact length M
        ensuref((int)spot[i].length() == M,
                "Length of spotty genome on line %d is %d but expected %d",
                2 + i, (int)spot[i].length(), M);
        inf.readEoln();
    }

    // Read plain cow genomes
    vector<string> plain(N);
    for (int i = 0; i < N; i++) {
        plain[i] = inf.readToken("[ACGT]+", "plain_seq");
        // Ensure exact length M
        ensuref((int)plain[i].length() == M,
                "Length of plain genome on line %d is %d but expected %d",
                2 + N + i, (int)plain[i].length(), M);
        inf.readEoln();
    }

    // Ensure no spotty genome exactly matches any plain genome
    unordered_set<string> spotSet;
    spotSet.reserve(N * 2);
    for (const auto &s : spot) {
        spotSet.insert(s);
    }
    for (int i = 0; i < N; i++) {
        ensuref(!spotSet.count(plain[i]),
                "Plain genome on line %d is identical to a spotty genome",
                2 + N + i);
    }

    // No extra content
    inf.readEof();
    return 0;
}
