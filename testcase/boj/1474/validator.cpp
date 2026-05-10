#include "testlib.h"
#include <string>
#include <cctype>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 10, "N");
    inf.readSpace();
    int M = inf.readInt(3, 200, "M");
    inf.readEoln();

    // Read N words
    long long totalLen = 0;
    for (int i = 0; i < N; i++) {
        // Read the word token (match-all, then validate)
        string w = inf.readToken("[^]+", ("word_" + to_string(i+1)).c_str());
        // Check length
        ensuref((int)w.size() >= 1 && (int)w.size() <= 10,
                "Length of word_%d must be between 1 and 10, but got %d",
                i+1, (int)w.size());
        // Check characters
        for (int j = 0; j < (int)w.size(); j++) {
            char c = w[j];
            ensuref((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'),
                    "Invalid character '%c' in word_%d at position %d", c, i+1, j+1);
        }
        totalLen += w.size();
        inf.readEoln();
    }

    // Check the sum constraint: len + N - 1 <= M
    ensuref(totalLen + N - 1 <= M,
            "Sum of lengths of words (%d) plus N-1 (%d) must be <= M (%d), but %d + %d > %d",
            (int)totalLen, N-1, M, (int)totalLen, N-1, M);

    inf.readEof();
    return 0;
}
