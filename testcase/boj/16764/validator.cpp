#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read number of cows
    int N = inf.readInt(2, 50000, "N");
    inf.readEoln();
    // For each cow, read 5 distinct flavor IDs
    for (int i = 0; i < N; i++) {
        vector<int> v = inf.readInts(5, 1, 1000000, "flavor");
        inf.readEoln();
        // Check all 5 are distinct
        sort(v.begin(), v.end());
        for (int j = 0; j + 1 < 5; j++) {
            ensuref(v[j] != v[j+1],
                "Duplicate flavor %d found on line %d", v[j], i+2);
        }
    }
    inf.readEof();
    return 0;
}
