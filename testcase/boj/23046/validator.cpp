#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single line containing the query string T.
    // We read all characters (including '-') then perform manual checks.
    string T = inf.readLine("[^]+", "T");

    // Check length constraints: 1 <= |T| <= 2,000,000
    int n = (int)T.size();
    ensuref(n >= 1 && n <= 2000000,
            "Length of T must be between 1 and 2000000, found %d", n);

    // First character must not be '-'
    ensuref(T[0] != '-',
            "First character of T must not be '-', but found '-' at position 1");

    // Check each character is either '1'..'9' or '-'
    for (int i = 0; i < n; i++) {
        char c = T[i];
        bool ok = (c >= '1' && c <= '9') || (c == '-');
        ensuref(ok,
                "Invalid character T[%d] = '%c'; only '1'..'9' or '-' allowed", i+1, c);
    }

    // The input must end immediately after this single newline.
    inf.readEof();

    return 0;
}
