#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters to skew distributions: negative for low bias, positive for high bias, zero for uniform
    vector<int> skew = {-2, -1, 0, 1, 2};
    int tW = rnd.any(skew);
    int tK = rnd.any(skew);

    // Generate W university scores
    for (int i = 0; i < 10; i++) {
        println(rnd.wnext(101, tW));
    }
    // Generate K university scores
    for (int i = 0; i < 10; i++) {
        println(rnd.wnext(101, tK));
    }

    return 0;
}
