#include "testlib.h"
#include <set>
#include <vector>
#include <string>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read M
    int M = inf.readInt(1, 200000, "M");
    inf.readEoln();

    // 2. Prepare to check for at least one type 3 query
    int count_type3 = 0;

    // 3. Prepare to simulate the array A
    // Since x can be up to 1e9, use map or unordered_map for counts
    // But since we only need to check for existence for type 2, and simulate, use map<int, int>
    // But for speed, use unordered_map
    #include <unordered_map>
    unordered_map<int, int> freq;
    freq[0] = 1; // 0 is always initially present

    // 4. For each query
    for (int i = 0; i < M; ++i) {
        int type = inf.readInt(1, 3, "type");
        inf.readSpace();
        int x = inf.readInt(1, 1000000000, "x");
        inf.readEoln();

        if (type == 1) {
            // Add x to A
            freq[x]++;
        } else if (type == 2) {
            // Remove x from A, x must exist
            ensuref(freq.count(x) && freq[x] > 0, "Query %d: Attempt to remove x=%d which does not exist in A", i+1, x);
            freq[x]--;
            if (freq[x] == 0) freq.erase(x);
        } else if (type == 3) {
            // Query: must be at least one such query
            count_type3++;
            // No further validation needed for type 3
        }
    }

    ensuref(count_type3 >= 1, "There must be at least one type 3 query.");

    inf.readEof();
}
