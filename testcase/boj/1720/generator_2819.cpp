#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Use weighted sampling to bias towards small, medium, or large N
    vector<int> weights = {-3, -1, 0, 1, 3};
    int t = rnd.any(weights);
    // rnd.wnext(30, t) yields a number in [0,29] with bias; +1 shifts to [1,30]
    int N = rnd.wnext(30, t) + 1;
    println(N);
    return 0;
}
