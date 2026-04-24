#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diverse N selection:
    // cluster 0: small, cluster 1: medium, cluster 2: large
    vector<int> clusters = {0,0,1,1,1,1,1,2,2};
    int cl = rnd.any(clusters);

    int N;
    if (cl == 0) {
        // small cluster (mostly 4–10, occasionally the minimum 3)
        if (rnd.next(0, 4) == 0)
            N = 3;
        else
            N = rnd.next(4, 10);
    }
    else if (cl == 1) {
        // medium cluster 11–50
        N = rnd.next(11, 50);
    }
    else {
        // large cluster (mostly 51–99, occasionally the maximum 100)
        if (rnd.next(0, 4) == 0)
            N = 100;
        else
            N = rnd.next(51, 99);
    }

    // Output a single integer N
    println(N);
    return 0;
}
