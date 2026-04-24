#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of test cases T in [1,10]
    vector<int> tvals = {-2, 0, 2};
    int tt = rnd.any(tvals);
    int T = rnd.wnext(10, tt) + 1;
    println(T);

    // Hyper-parameters for n and m distributions
    vector<int> ntvals = {-3, -1, 0, 1, 3};
    vector<int> mtvals = {-2, 0, 2};

    for (int i = 0; i < T; i++) {
        // n in [2,100], biased by nt
        int nt = rnd.any(ntvals);
        int n = rnd.wnext(99, nt) + 2;

        // m in [1,100], biased by mt
        int mt = rnd.any(mtvals);
        int m = rnd.wnext(100, mt) + 1;

        println(n, m);
    }

    return 0;
}
