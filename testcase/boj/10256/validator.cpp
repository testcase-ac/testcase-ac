#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read n and m
        int n = inf.readInt(1, 1000000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 100, "m");
        inf.readEoln();

        // Read DNA string
        string dna = inf.readLine("[^]+", "dna");
        // Validate length
        ensuref((int)dna.size() == n,
                "Length of dna string (%d) does not match n (%d) in test case %d",
                (int)dna.size(), n, tc);
        // Validate characters
        for (int i = 0; i < n; i++) {
            char c = dna[i];
            ensuref(c == 'A' || c == 'C' || c == 'G' || c == 'T',
                    "Invalid character in dna at position %d: '%c' (test case %d)",
                    i+1, c, tc);
        }

        // Read marker string
        string marker = inf.readLine("[^]+", "marker");
        // Validate length
        ensuref((int)marker.size() == m,
                "Length of marker string (%d) does not match m (%d) in test case %d",
                (int)marker.size(), m, tc);
        // Validate characters
        for (int i = 0; i < m; i++) {
            char c = marker[i];
            ensuref(c == 'A' || c == 'C' || c == 'G' || c == 'T',
                    "Invalid character in marker at position %d: '%c' (test case %d)",
                    i+1, c, tc);
        }
    }

    inf.readEof();
    return 0;
}
