#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);

    // Possible maximum values for diversity
    vector<int> maxOpts = {10, 20, 100, 1000, 10000};

    for (int i = 0; i < T; i++) {
        // Hyper-parameter t for uneven N distribution
        int t = rnd.next(-3, 3);
        // Generate N in [1,10] with bias
        int N = rnd.wnext(10, t) + 1;
        // Choose a max value for elements
        int maxV = rnd.any(maxOpts);

        // Generate the numbers for this test case
        vector<int> v(N);
        for (int j = 0; j < N; j++) {
            v[j] = rnd.next(1, maxV);
        }

        // Output the test case line
        println(v);
    }

    return 0;
}
