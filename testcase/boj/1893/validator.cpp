#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

bool isAlphabetSymbol(char c) {
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || ('0' <= c && c <= '9');
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxCases = 100000;
    const int maxTotalChars = 10000000;

    // CHECK: The statement gives no upper bound for N; use the local default cap.
    int n = inf.readInt(1, maxCases, "N");
    inf.readEoln();

    int totalChars = 0;
    for (int tc = 1; tc <= n; ++tc) {
        setTestCase(tc);

        string alphabet = inf.readToken("[A-Za-z0-9]{3,62}", "A");
        inf.readEoln();

        vector<bool> inAlphabet(256, false);
        for (char c : alphabet) {
            unsigned char uc = static_cast<unsigned char>(c);
            ensuref(!inAlphabet[uc], "duplicate character '%c' in alphabet", c);
            inAlphabet[uc] = true;
        }

        string word = inf.readToken("[A-Za-z0-9]{1,50000}", "W");
        inf.readEoln();
        string encrypted = inf.readToken("[A-Za-z0-9]{3,500000}", "S");
        inf.readEoln();

        for (char c : word) {
            ensuref(isAlphabetSymbol(c), "word contains invalid symbol '%c'", c);
            ensuref(inAlphabet[static_cast<unsigned char>(c)],
                    "word symbol '%c' is not present in alphabet", c);
        }
        for (char c : encrypted) {
            ensuref(isAlphabetSymbol(c), "encrypted text contains invalid symbol '%c'", c);
            ensuref(inAlphabet[static_cast<unsigned char>(c)],
                    "encrypted text symbol '%c' is not present in alphabet", c);
        }

        totalChars += int(alphabet.size()) + int(word.size()) + int(encrypted.size());
        // CHECK: Per-case bounds allow impractically huge aggregate input; cap total string bytes.
        ensuref(totalChars <= maxTotalChars,
                "total string length exceeds practical cap %d", maxTotalChars);
    }

    inf.readEof();
    return 0;
}
