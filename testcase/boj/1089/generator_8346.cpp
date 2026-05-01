#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Seven-segment-like patterns for digits 0-9 (5 rows x 3 cols)
    vector<vector<string>> DIG = {
        {"###", "#.#", "#.#", "#.#", "###"}, // 0
        {"..#", "..#", "..#", "..#", "..#"}, // 1
        {"###", "..#", "###", "#..", "###"}, // 2
        {"###", "..#", "###", "..#", "###"}, // 3
        {"#.#", "#.#", "###", "..#", "..#"}, // 4
        {"###", "#..", "###", "..#", "###"}, // 5
        {"###", "#..", "###", "#.#", "###"}, // 6
        {"###", "..#", "..#", "..#", "..#"}, // 7
        {"###", "#.#", "###", "#.#", "###"}, // 8
        {"###", "#.#", "###", "..#", "###"}  // 9
    };

    // Hyper-parameter for N: skewed random from 1 to 9
    int tN = rnd.any(vector<int>{-2, -1, 0, 1, 2});
    int N = rnd.wnext(9, tN) + 1;

    // Sample a true floor number in [0, 10^N - 1]
    long long maxNum = 1;
    for (int i = 0; i < N; i++) maxNum *= 10;
    long long trueNum = rnd.next(0LL, maxNum - 1);
    vector<int> trueDigits(N);
    for (int i = N - 1; i >= 0; i--) {
        trueDigits[i] = trueNum % 10;
        trueNum /= 10;
    }

    // Hyper-parameter for broken-bulb probability p in [0.0,1.0]
    int tp = rnd.any(vector<int>{-2, -1, 0, 1, 2});
    int pp = rnd.wnext(101, tp); // 0..100
    double p = pp / 100.0;

    // Build the observed 5 x (4N-1) board
    int W = 4 * N - 1;
    vector<string> out(5, string(W, '.'));
    for (int i = 0; i < N; i++) {
        int d = trueDigits[i];
        int off = i * 4;
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 3; c++) {
                if (DIG[d][r][c] == '#') {
                    // broken with probability p
                    if (rnd.next() < p) {
                        // remains '.'
                    } else {
                        out[r][off + c] = '#';
                    }
                }
            }
        }
        // separator column (off+3) stays '.'
    }

    // Output
    println(N);
    for (int r = 0; r < 5; r++) {
        println(out[r]);
    }

    return 0;
}
