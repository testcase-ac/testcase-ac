#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    vector<int> range_choices = {0, 1, 2, 5, 10, 50, 100, 1000};
    vector<int> t_choices = {1, 2, 3, 5, 8, 10};

    // Number of test cases (excluding the terminating 0 0 0 0)
    int T = rnd.any(t_choices);

    for (int i = 0; i < T; i++) {
        // Pick a in [-5000, 2000]
        int a = rnd.next(-5000, 2000);
        // Birth interval length
        int b_max = rnd.any(range_choices);
        int birth_gap = rnd.next(0, b_max);
        int b = a + birth_gap;
        if (b > 2000) b = 2000;

        // Death lower bound c >= b
        int c_max = rnd.any(range_choices);
        int c_gap = rnd.next(0, c_max);
        int c = b + c_gap;
        if (c > 2000) c = 2000;

        // Death upper bound d >= c
        int d_max = rnd.any(range_choices);
        int d_gap = rnd.next(0, d_max);
        int d = c + d_gap;
        if (d > 2000) d = 2000;

        // Output one test case
        println(a, b, c, d);
    }

    // Terminate input
    println(0, 0, 0, 0);
    return 0;
}
