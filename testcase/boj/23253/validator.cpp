#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int M = inf.readInt(1, N, "M"); // 1 <= M <= N
    inf.readEoln();

    // Prepare to count occurrences of each book
    vector<int> cnt(N+1, 0);
    long long sumk = 0;

    // Read each stack
    for (int i = 0; i < M; i++) {
        // Read k_i
        int ki = inf.readInt(1, N, "k_i");
        sumk += ki;
        inf.readEoln();

        // Read the books on this stack (bottom to top)
        vector<int> stack = inf.readInts(ki, 1, N, "book");
        inf.readEoln();

        // Check for duplicates across all stacks
        for (int j = 0; j < ki; j++) {
            int b = stack[j];
            ensuref(cnt[b] == 0,
                    "Book %d appears multiple times (at stack %d, position %d)",
                    b, i+1, j+1);
            cnt[b]++;
        }
    }

    // Sum of k_i must be exactly N
    ensuref(sumk == N, "Sum of all k_i must be N, but sum is %d", sumk);

    // Each book from 1 to N must appear exactly once
    for (int b = 1; b <= N; b++) {
        ensuref(cnt[b] == 1, "Book %d is missing", b);
    }

    inf.readEof();
    return 0;
}
