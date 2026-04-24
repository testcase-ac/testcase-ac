#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);
    for (int i = 0; i < T; i++) {
        double p = rnd.next();
        int K;
        if (p < 0.3) {
            // Small K biased towards lower end [3,50]
            K = rnd.wnext(48, -1) + 3;  // rnd.wnext(48,-1) in [0,47]
        } else if (p < 0.6) {
            // Medium K uniformly in [51,500]
            K = rnd.next(51, 500);
        } else {
            // Large K uniformly in [501,1000]
            K = rnd.next(501, 1000);
        }
        println(K);
    }
    return 0;
}
