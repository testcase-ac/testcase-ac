#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 400, "N");
    inf.readSpace();
    int M = inf.readInt(1, 400, "M");
    inf.readEoln();

    // Read each employee's capability list
    for (int i = 1; i <= N; i++) {
        // k_i: number of tasks employee i can do
        int k = inf.readInt(0, M, "k");
        vector<int> jobs;
        if (k > 0) {
            // space before the list
            inf.readSpace();
            for (int j = 0; j < k; j++) {
                // task index
                int job = inf.readInt(1, M, "job");
                inf.readSpace();
                // wage for that task
                int wage = inf.readInt(0, 10000, "wage");
                jobs.push_back(job);
                // space between pairs, but not after last
                if (j + 1 < k) {
                    inf.readSpace();
                }
            }
        }
        // end of this line
        inf.readEoln();

        // ensure no duplicate tasks in this employee's list
        set<int> seen(jobs.begin(), jobs.end());
        ensuref(seen.size() == jobs.size(),
                "Duplicate task index found in employee %d's list", i);
    }

    inf.readEof();
    return 0;
}
