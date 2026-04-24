#include "testlib.h"

#include <vector>
#include <numeric>
#include <algorithm>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readSpace();
    int k = inf.readInt(1, n, "k"); // Constraint: 1 <= K <= N
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int c_i = inf.readInt(0, m, "c_i"); // Constraint: 0 <= c_i <= M
        
        if (c_i > 0) {
            inf.readSpace(); // Space before reading job IDs if c_i > 0
            vector<int> jobs = inf.readInts(c_i, 1, m, "job_id"); // Constraint: Job IDs 1 to M
            
            // Check for distinct job IDs for this employee
            set<int> distinct_jobs;
            for (int job_id : jobs) {
                ensuref(distinct_jobs.find(job_id) == distinct_jobs.end(), 
                        "Employee %d has duplicate job ID %d in their list.", i, job_id);
                distinct_jobs.insert(job_id);
            }
            
            inf.readEoln(); // EOLN after reading c_i job IDs
        } else { // c_i == 0
            inf.readEoln(); // Just EOLN after reading c_i=0
        }
    }

    inf.readEof();
}
