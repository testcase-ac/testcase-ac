#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K and N
    int K = inf.readInt(1, 10, "K");
    inf.readSpace();
    int N = inf.readInt(1, 20, "N");
    inf.readEoln();

    // Each of the K lines is a permutation of 1..N
    for (int session = 1; session <= K; session++) {
        vector<int> ranking = inf.readInts(N, 1, N, "ranking");
        inf.readEoln();

        // Check it's a permutation: no duplicates, no missing values
        vector<bool> seen(N+1, false);
        for (int pos = 0; pos < N; pos++) {
            int cow = ranking[pos];
            ensuref(!seen[cow],
                    "Duplicate cow %d in session %d at position %d",
                    cow, session, pos+1);
            seen[cow] = true;
        }
        for (int cow = 1; cow <= N; cow++) {
            ensuref(seen[cow],
                    "Cow %d missing in session %d",
                    cow, session);
        }
    }

    inf.readEof();
    return 0;
}
