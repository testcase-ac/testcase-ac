#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(5, 100000, "N");
    ensuref(N % 5 == 0, "N must be divisible by 5, but N = %d", N);
    inf.readEoln();

    // Read the signal line
    string s = inf.readToken("[.#]+", "signal");
    ensuref((int)s.size() == N, "Length of signal must be N = %d, but got %d", N, (int)s.size());
    inf.readEoln();

    // Build 5-row grid: each row has M = N/5 columns
    int M = N / 5;
    vector<string> row(5);
    for (int i = 0; i < 5; i++) {
        row[i] = s.substr(i * M, M);
    }

    // Define digit patterns
    // Each pattern is 5 strings of length 1 (for '1') or 3 (for others)
    vector<vector<string>> pat(10);
    pat[0] = {"###", "#.#", "#.#", "#.#", "###"};
    pat[1] = {"#",   "#",   "#",   "#",   "#"};
    pat[2] = {"###", "..#", "###", "#..", "###"};
    pat[3] = {"###", "..#", "###", "..#", "###"};
    pat[4] = {"#.#", "#.#", "###", "..#", "..#"};
    pat[5] = {"###", "#..", "###", "..#", "###"};
    pat[6] = {"###", "#..", "###", "#.#", "###"};
    pat[7] = {"###", "..#", "..#", "..#", "..#"};
    pat[8] = {"###", "#.#", "###", "#.#", "###"};
    pat[9] = {"###", "#.#", "###", "..#", "###"};

    // Scan columns to extract segments
    int j = 0;
    int digitCount = 0;
    while (j < M) {
        // Skip blank columns
        if (true) {
            bool isBlank = true;
            for (int r = 0; r < 5; r++) {
                if (row[r][j] == '#') {
                    isBlank = false;
                    break;
                }
            }
            if (isBlank) {
                j++;
                continue;
            }
        }
        // Now row[*][j] has at least one '#', start of a segment
        int start = j;
        while (j < M) {
            bool isBlank = true;
            for (int r = 0; r < 5; r++) {
                if (row[r][j] == '#') {
                    isBlank = false;
                    break;
                }
            }
            if (isBlank) break;
            j++;
        }
        int end = j - 1;
        int width = end - start + 1;
        // Segment width must be 1 or 3
        ensuref(width == 1 || width == 3,
                "Invalid segment width %d at columns [%d..%d]; must be 1 or 3",
                width, start, end);

        // Extract the sub-grid
        vector<string> sub(5);
        for (int r = 0; r < 5; r++) {
            sub[r] = row[r].substr(start, width);
        }

        // Match with a digit pattern
        int matched = -1;
        for (int d = 0; d < 10; d++) {
            if ((int)pat[d][0].size() != width) continue;
            bool ok = true;
            for (int r = 0; r < 5 && ok; r++) {
                if (sub[r] != pat[d][r]) ok = false;
            }
            if (ok) {
                matched = d;
                break;
            }
        }
        ensuref(matched != -1, "Unknown digit pattern at columns [%d..%d]", start, end);
        digitCount++;
    }

    ensuref(digitCount >= 1, "At least one digit must appear, but found %d", digitCount);

    inf.readEof();
    return 0;
}
