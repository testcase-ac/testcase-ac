#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Dimensions
    int N = rnd.next(1, 6);
    int M = rnd.next(1, 6);

    // Decide if the test case should be correct or incorrect
    bool correct = rnd.next(2) == 0;

    // Character pool
    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int L = (int)letters.size();

    // Generate the original N x M image
    vector<string> orig(N);
    for (int i = 0; i < N; i++) {
        // hyper-parameter: uniform row vs fully random row
        bool uniform = rnd.next(2) == 0;
        char fill = letters[rnd.next(0, L-1)];
        for (int j = 0; j < M; j++) {
            if (uniform)
                orig[i] += fill;
            else
                orig[i] += letters[rnd.next(0, L-1)];
        }
    }

    // Build the stretched image by doubling each character
    vector<string> stretched(N);
    for (int i = 0; i < N; i++) {
        string t;
        for (char c : orig[i]) {
            t.push_back(c);
            t.push_back(c);
        }
        stretched[i] = t;
    }

    // If we want an incorrect case, introduce exactly one mismatch
    if (!correct) {
        int row = rnd.next(0, N-1);
        int col = rnd.next(0, 2*M-1);
        char bad;
        do {
            bad = letters[rnd.next(0, L-1)];
        } while (bad == stretched[row][col]);
        stretched[row][col] = bad;
    }

    // Output format
    println(N, M);
    for (auto &s : orig)      println(s);
    for (auto &s : stretched) println(s);

    return 0;
}
