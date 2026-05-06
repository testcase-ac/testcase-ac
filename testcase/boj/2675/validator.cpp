#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // QR Code alphanumeric characters:
    // 0-9, A-Z, and the symbols $ % * + - . / :
    const string allowed = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ$%*+\\-./:";

    for (int tc = 0; tc < T; ++tc) {
        // Repetition count
        int R = inf.readInt(1, 8, "R");
        inf.readSpace();
        // Input string S: length 1..20, all chars must be in the allowed set
        string S = inf.readToken("[^]+", "S");
        // Check length
        ensuref((int)S.size() >= 1 && (int)S.size() <= 20,
                "Length of S must be between 1 and 20, got %d", (int)S.size());
        // Check each character
        for (int i = 0; i < (int)S.size(); ++i) {
            char c = S[i];
            bool ok = false;
            // Check membership in allowed set
            if ('0' <= c && c <= '9') ok = true;
            else if ('A' <= c && c <= 'Z') ok = true;
            else {
                // Check the nine punctuation symbols
                const string sym = "$%*+ -./:";
                if (sym.find(c) != string::npos) ok = true;
            }
            ensuref(ok, "Invalid character S[%d] = '%c'", i, c);
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
