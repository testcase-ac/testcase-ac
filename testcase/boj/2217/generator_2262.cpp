#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameter 1: number of ropes (small for human verification)
    int N = rnd.next(1, 10);
    println(N);

    // Hyperparameter 2: distribution type of rope strengths
    // 1 = full range [1,10000]
    // 2 = small range [1,100]
    // 3 = few distinct values
    int dist_type = rnd.next(1, 3);

    for (int i = 0; i < N; i++) {
        int s;
        if (dist_type == 1) {
            // uniform over full allowed range
            s = rnd.next(1, 10000);
        } else if (dist_type == 2) {
            // more clustered small strengths
            s = rnd.next(1, 100);
        } else {
            // few distinct “corner” values
            static int pool[] = {1, 10, 100, 1000, 5000, 10000};
            s = pool[rnd.next(0, 5)];
        }
        println(s);
    }
    return 0;
}
