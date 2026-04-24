#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for different outcome types
    vector<int> errorNs   = {3, 5, 7, 9};      // N odd >=3 => compile error
    vector<int> finiteNs  = {2, 4, 6, 8, 10};  // N even >=2 => finite prints
    vector<int> smallNs   = {0, 1};            // possible infinite cases

    int type = rnd.next(0, 2);
    int N, X;
    if (type == 0) {
        // ERROR case
        N = rnd.any(errorNs);
        X = rnd.next(-100, 100);
    } else if (type == 1) {
        // INFINITE case
        N = rnd.any(smallNs);
        if (N == 0)       // while(0 < x) with x>0 => never changes => infinite
            X = rnd.next(1, 100);
        else              // N==1 => while(0 < -x) with x<0 => infinite
            X = rnd.next(-100, -1);
    } else {
        // FINITE case
        N = rnd.any(finiteNs);
        X = rnd.next(-100, 100);
    }

    println(X, N);
    return 0;
}
