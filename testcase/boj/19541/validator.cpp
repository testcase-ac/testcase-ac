#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Check meetings
    long long sum_k = 0;
    vector<char> seen(N + 1, 0);
    vector<int> used;

    for (int mi = 1; mi <= M; mi++) {
        // Read size of meeting
        int k = inf.readInt(2, N, "k");
        sum_k += k;
        ensuref(sum_k <= 1000000LL,
                "Sum of all k exceeds 1e6 at meeting %d (current sum %lld)", mi, sum_k);

        // Read participants
        inf.readSpace();
        vector<int> a = inf.readInts(k, 1, N, "a_i");
        inf.readEoln();

        // Check distinctness within the meeting
        used.clear();
        for (int x : a) {
            ensuref(!seen[x],
                    "Duplicate participant %d in meeting %d", x, mi);
            seen[x] = 1;
            used.push_back(x);
        }
        // Reset seen flags
        for (int x : used) {
            seen[x] = 0;
        }
    }

    // Read final infection statuses
    vector<int> fin = inf.readInts(N, 0, 1, "final_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
