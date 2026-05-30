#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // For each employee, read the count of doable jobs and the list
    for (int i = 1; i <= N; i++) {
        // c = number of jobs employee i can do
        int c = inf.readInt(0, M, "c_i");
        vector<int> jobs;
        if (c > 0) {
            // there must be a space before the list of jobs
            inf.readSpace();
            jobs = inf.readInts(c, 1, M, "job");
        }
        inf.readEoln();

        // CHECK: The statement describes a list of job numbers but does not
        // explicitly require distinct job numbers within one employee's list.
    }

    // No extra data
    inf.readEof();
    return 0;
}
