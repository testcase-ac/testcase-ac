#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the entire line as S (may be empty), then validate its properties.
    string S = inf.readLine("[^]*", "S");
    
    // Length constraint: at most 50 characters.
    ensuref((int)S.size() <= 50,
            "Length of S is %d, but must be at most 50", (int)S.size());
    
    // No leading or trailing spaces in the input line.
    if (!S.empty()) {
        ensuref(S.front() != ' ',
                "S must not start with a space, but S[0] is a space");
        ensuref(S.back() != ' ',
                "S must not end with a space, but S[last] is a space");
    }
    
    // Allowed characters: uppercase, lowercase, space, and double-quote.
    for (int i = 0; i < (int)S.size(); i++) {
        char c = S[i];
        bool ok = false;
        if (c == '"') ok = true;
        else if (c == ' ') ok = true;
        else if ('a' <= c && c <= 'z') ok = true;
        else if ('A' <= c && c <= 'Z') ok = true;
        ensuref(ok,
                "Invalid character at position %d: '%c'. "
                "Allowed are A-Z, a-z, space, and '\"'", 
                i, c);
    }
    
    // Count the number of double-quote characters: must be at most 2.
    int quote_count = 0;
    for (char c : S) if (c == '"') quote_count++;
    ensuref(quote_count <= 2,
            "S contains %d quotes, but must contain at most 2", quote_count);
    
    // If there are exactly two quotes, ensure no spaces immediately inside them.
    if (quote_count == 2) {
        int p1 = S.find('"');
        int p2 = S.find_last_of('"');
        // p1 < p2 by construction when count==2
        // If there is at least one character between quotes, it must not be space at the ends.
        if (p1 + 1 < p2) {
            ensuref(S[p1+1] != ' ',
                    "Space detected immediately after opening quote at position %d", p1);
            ensuref(S[p2-1] != ' ',
                    "Space detected immediately before closing quote at position %d", p2);
        }
    }
    
    // The statement says: exactly one line of input, then EOF.
    inf.readEof();
    return 0;
}
