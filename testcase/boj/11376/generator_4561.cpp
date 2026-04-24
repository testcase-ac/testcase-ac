#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);
    println(N, M);

    // Prepare task list
    vector<int> allTasks(M);
    iota(allTasks.begin(), allTasks.end(), 1);

    // For diversity, use weighted sampling for each worker's capacity
    vector<int> modes = {-2, 0, 2};
    for (int i = 0; i < N; i++) {
        // Choose a bias: negative -> small degrees, positive -> large degrees, zero -> uniform
        int mode = rnd.any(modes);
        int Ci = rnd.wnext(M + 1, mode);
        if (Ci > M) Ci = M;

        // Pick Ci distinct tasks
        shuffle(allTasks.begin(), allTasks.end());
        vector<int> tasks(allTasks.begin(), allTasks.begin() + Ci);

        // Output this worker's line
        printf("%d", Ci);
        for (int t : tasks)
            printf(" %d", t);
        printf("\n");
    }

    return 0;
}
