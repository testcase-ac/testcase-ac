#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCnt = 0;
    while (true) {
        // Read first line of a case or sentinel
        string s = inf.readLine("[^]+", "word1");
        if (s == "END") {
            // Expect second sentinel line
            string t = inf.readLine("[^]+", "word2_sentinel");
            ensuref(t == "END", "After first END sentinel, expected second END but got '%s'", t.c_str());
            break;
        }
        // Validate word1: only lowercase letters, length 1..1000
        ensuref((int)s.size() >= 1 && (int)s.size() <= 1000,
                "Length of word1 must be between 1 and 1000, got %d", (int)s.size());
        for (int i = 0; i < (int)s.size(); i++) {
            char c = s[i];
            ensuref(c >= 'a' && c <= 'z',
                    "word1 must contain only lowercase letters, but s[%d] = '%c'", i, c);
        }

        // Read and validate word2
        string t = inf.readLine("[^]+", "word2");
        ensuref((int)t.size() >= 1 && (int)t.size() <= 1000,
                "Length of word2 must be between 1 and 1000, got %d", (int)t.size());
        for (int i = 0; i < (int)t.size(); i++) {
            char c = t[i];
            ensuref(c >= 'a' && c <= 'z',
                    "word2 must contain only lowercase letters, but t[%d] = '%c'", i, c);
        }

        // Count and limit number of cases
        caseCnt++;
        ensuref(caseCnt <= 100000,
                "Number of cases exceeds limit: %d > 100000", caseCnt);
    }

    inf.readEof();
    return 0;
}
