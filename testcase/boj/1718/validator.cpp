#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the plaintext line: can be empty, up to 30000 chars, only 'a'..'z' and spaces.
    // We read any characters (except newline) and then validate manually.
    string plaintext = inf.readLine("[^]*", "plaintext");
    // Check length constraint
    ensuref(plaintext.size() <= 30000,
            "Plaintext length exceeds 30000: %d", (int)plaintext.size());
    // Check allowed characters
    for (int i = 0; i < (int)plaintext.size(); i++) {
        char c = plaintext[i];
        ensuref((c >= 'a' && c <= 'z') || c == ' ',
                "Invalid character in plaintext at position %d: '%c'", i, c);
    }

    // Read the key: must be non-empty, only lowercase letters, and length ≤ 30000
    // We use readToken since key has no spaces.
    string key = inf.readToken("[a-z]+", "key");
    ensuref(key.size() <= 30000,
            "Key length exceeds 30000: %d", (int)key.size());

    // After the key token, there must be exactly one newline
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
