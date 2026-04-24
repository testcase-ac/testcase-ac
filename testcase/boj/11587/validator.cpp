#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read N words, check total length <= 1e6
    long long total_len = 0;
    for (int i = 0; i < N; i++) {
        // each word: lowercase letters only, at least one character
        string w = inf.readLine("[a-z]+", "word");
        total_len += (long long)w.size();
        ensuref(total_len <= 1000000LL,
                "Sum of lengths of words exceeds 1000000 after reading word %d (current sum = %lld)",
                i + 1, total_len);
    }

    // Read S: digits 2-9 only, length 1..1000
    string S = inf.readLine("[2-9]+", "S");
    ensuref((int)S.size() <= 1000,
            "Length of S exceeds 1000: %d", (int)S.size());
    // No more input
    inf.readEof();
    return 0;
}
