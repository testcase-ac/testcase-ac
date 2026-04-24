#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // For each of the N employees, read their list
    for (int i = 1; i <= N; i++) {
        // k_i: number of jobs this employee can do
        int k = inf.readInt(0, M, "k");
        set<int> seen;
        if (k > 0) {
            // Read k job indices
            for (int j = 0; j < k; j++) {
                inf.readSpace();
                int job = inf.readInt(1, M, "job");
                // Check for duplicates in this employee's list
                ensuref(!seen.count(job),
                        "Duplicate job %d in employee %d's list", job, i);
                seen.insert(job);
            }
        }
        // End of this line
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
