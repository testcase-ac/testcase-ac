#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 30, "n");
    inf.readSpace();
    int m = inf.readInt(n + 1, 100, "m");
    inf.readEoln();

    // Read the last n letters of the plaintext
    string last = inf.readToken("[a-z]+", "last_plaintext");
    inf.readEoln();
    ensuref((int)last.size() == n,
            "The second line must have exactly n = %d lowercase letters, but has %d",
            n, (int)last.size());

    // Read the ciphertext of length m
    string cipher = inf.readToken("[a-z]+", "ciphertext");
    inf.readEoln();
    ensuref((int)cipher.size() == m,
            "The third line must have exactly m = %d lowercase letters, but has %d",
            m, (int)cipher.size());

    // No more input
    inf.readEof();
    return 0;
}
