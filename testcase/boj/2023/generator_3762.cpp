#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose between uniform or weighted sampling
    bool useWeighted = rnd.next(2); // 0 or 1
    int N;
    if (useWeighted) {
        // weighted parameter to bias small or large N
        vector<int> ts = {-2, -1, 0, 1, 2};
        int t = rnd.any(ts);
        // rnd.wnext(8, t) yields [0..7], so add 1 to get [1..8]
        N = rnd.wnext(8, t) + 1;
    } else {
        // uniform sampling from 1 to 8
        N = rnd.next(1, 8);
    }

    // Output single integer N
    println(N);
    return 0;
}
