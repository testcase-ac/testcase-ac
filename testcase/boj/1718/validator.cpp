#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read a nonempty plaintext line of up to 30000 lowercase letters and spaces.
    // We read any characters (except newline) and then validate manually.
    string plaintext = inf.readLine("[^]*", "plaintext");
    // Check length constraint
    ensuref(plaintext.size() <= 30000,
            "Plaintext length exceeds 30000: %d", (int)plaintext.size());
    // Check allowed characters
    bool hasLetter = false;
    for (int i = 0; i < (int)plaintext.size(); i++) {
        char c = plaintext[i];
        ensuref((c >= 'a' && c <= 'z') || c == ' ',
                "Invalid character in plaintext at position %d: '%c'", i, c);
        hasLetter = hasLetter || (c >= 'a' && c <= 'z');
    }
    ensuref(hasLetter, "Plaintext must contain at least one lowercase letter");
    ensuref(plaintext.front() != ' ' && plaintext.back() != ' ',
            "Plaintext must not have leading or trailing spaces");

    // Read the key: must be non-empty and only lowercase letters.
    // We use readToken since key has no spaces.
    string key = inf.readToken("[a-z]+", "key");

    // After the key token, there must be exactly one newline
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
