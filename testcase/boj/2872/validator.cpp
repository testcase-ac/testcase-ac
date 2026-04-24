#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of books
    int N = inf.readInt(1, 300000, "N");
    inf.readEoln();

    // To check it is a permutation of [1..N]
    vector<char> seen(N+1, 0);
    for (int i = 0; i < N; i++) {
        // Read each book ID, must be in [1, N]
        int x = inf.readInt(1, N, "book_id");
        inf.readEoln();
        // No duplicates
        ensuref(!seen[x],
                "Duplicate book id %d at position %d", x, i+1);
        seen[x] = 1;
    }

    // Ensure every ID from 1 to N appears exactly once
    for (int x = 1; x <= N; x++) {
        ensuref(seen[x],
                "Missing book id %d", x);
    }

    inf.readEof();
    return 0;
}
