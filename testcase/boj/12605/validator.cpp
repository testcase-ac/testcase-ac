#include "testlib.h"
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of cases: 1 ≤ N ≤ 5
    int N = inf.readInt(1, 5, "N");
    inf.readEoln();

    for (int i = 1; i <= N; i++) {
        // Read the entire line (possibly empty, we'll check emptiness below)
        string line = inf.readLine("[^]*", "line");

        // Line must not be empty
        ensuref(!line.empty(), "Case %d: empty line", i);

        // Check characters and count total letters
        long long sumLetters = 0;
        for (int j = 0; j < (int)line.size(); j++) {
            char c = line[j];
            // only alphabetic or space allowed
            ensuref(c == ' ' || isalpha(c),
                    "Case %d, pos %d: invalid character '%c'", i, j+1, c);
            if (isalpha(c)) {
                sumLetters++;
            }
        }
        // Total letters L must satisfy 1 ≤ L ≤ 25
        ensuref(1 <= sumLetters && sumLetters <= 25,
                "Case %d: total letters %lld out of range [1,25]", i, sumLetters);

        // No leading or trailing spaces
        ensuref(line.front() != ' ', "Case %d: leading space", i);
        ensuref(line.back()  != ' ', "Case %d: trailing space", i);

        // No consecutive spaces
        for (int j = 0; j + 1 < (int)line.size(); j++) {
            ensuref(!(line[j] == ' ' && line[j+1] == ' '),
                    "Case %d: consecutive spaces at positions %d-%d", i, j+1, j+2);
        }
    }

    inf.readEof();
    return 0;
}
