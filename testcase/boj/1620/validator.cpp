#include "testlib.h"
#include <string>
#include <set>
#include <cctype>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read the N Pokemon names
    vector<string> names(N+1);
    set<string> nameSet;
    for (int i = 1; i <= N; i++) {
        // Read any non-empty line of letters 2..20 chars
        string s = inf.readLine("[A-Za-z]{2,20}", "pokemon_name");
        int L = (int)s.size();

        // Validate first character is uppercase
        ensuref(isupper(s[0]),
                "pokemon_name %d: first character must be uppercase, got '%c' in \"%s\"",
                i, s[0], s.c_str());

        // Validate characters 1..L-2 are lowercase (only if L>=3)
        for (int j = 1; j <= L-2; j++) {
            ensuref(islower(s[j]),
                    "pokemon_name %d: character at position %d must be lowercase, got '%c' in \"%s\"",
                    i, j+1, s[j], s.c_str());
        }
        // The last character (index L-1) may be lowercase or uppercase; it's already in [A-Za-z].

        // Check for duplicate names
        bool inserted = nameSet.insert(s).second;
        ensuref(inserted,
                "Duplicate pokemon name at index %d: \"%s\"",
                i, s.c_str());

        names[i] = s;
    }

    // Read the M queries
    for (int qidx = 1; qidx <= M; qidx++) {
        // Read the whole line (any chars except newline)
        string q = inf.readLine("[^]+", "query");
        int Lq = (int)q.size();
        ensuref(Lq > 0,
                "Query %d: empty line is not a valid query", qidx);

        // Determine if it's a numeric query (all digits)
        bool all_digits = true;
        for (char c : q) {
            if (!isdigit(c)) {
                all_digits = false;
                break;
            }
        }

        if (all_digits) {
            // Must not have leading zero
            ensuref(q[0] != '0',
                    "Query %d: leading zero in number query \"%s\"", qidx, q.c_str());
            // Parse and check range
            long long x = 0;
            // stoll is safe since q length <= 6 (N <= 100000)
            x = atoll(q.c_str());
            ensuref(1 <= x && x <= N,
                    "Query %d: number %lld out of valid range [1,%d]", qidx, x, N);
        }
        else {
            // Must be all alphabetic
            for (int j = 0; j < Lq; j++) {
                char c = q[j];
                ensuref(isalpha(c),
                        "Query %d: invalid character '%c' in query \"%s\"", qidx, c, q.c_str());
            }
            // Check length constraints for name queries
            ensuref(Lq >= 2 && Lq <= 20,
                    "Query %d: pokemon name length out of range (2..20): \"%s\"", qidx, q.c_str());
            // First char uppercase
            ensuref(isupper(q[0]),
                    "Query %d: first character of pokemon name must be uppercase in \"%s\"", qidx, q.c_str());
            // Characters 1..Lq-2 lowercase
            for (int j = 1; j <= Lq-2; j++) {
                ensuref(islower(q[j]),
                        "Query %d: character at position %d must be lowercase in \"%s\"", qidx, j+1, q.c_str());
            }
            // Last char may be any case letter

            // Must exist in the dictionary
            ensuref(nameSet.count(q),
                    "Query %d: unknown pokemon name \"%s\"", qidx, q.c_str());
        }
    }

    inf.readEof();
    return 0;
}
