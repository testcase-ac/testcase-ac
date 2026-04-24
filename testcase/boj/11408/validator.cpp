#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 400, "N");
    inf.readSpace();
    int M = inf.readInt(1, 400, "M");
    inf.readEoln();

    // For each employee, read their possible jobs and wages
    for (int i = 1; i <= N; i++) {
        int k = inf.readInt(0, M, "k_i");
        set<int> seenJobs;
        for (int j = 0; j < k; j++) {
            inf.readSpace();
            int job = inf.readInt(1, M, "job");
            inf.readSpace();
            int wage = inf.readInt(0, 10000, "wage");
            // Ensure no duplicate job entries for the same employee
            ensuref(seenJobs.insert(job).second,
                    "Duplicate job %d for employee %d", job, i);
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
