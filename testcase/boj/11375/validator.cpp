#include "testlib.h"
#include <vector>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // For each employee, read the number of tasks they can do and the task IDs
    for (int i = 1; i <= N; i++) {
        // k_i can be zero (employee who cannot do any job)
        int k = inf.readInt(0, M, "k_" + to_string(i));
        vector<char> seen(M+1, 0);
        for (int j = 1; j <= k; j++) {
            inf.readSpace();
            int t = inf.readInt(1, M, "task_" + to_string(i) + "_" + to_string(j));
            // No duplicate tasks in the list for a single employee
            ensuref(!seen[t],
                    "Duplicate task %d for employee %d", t, i);
            seen[t] = 1;
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
