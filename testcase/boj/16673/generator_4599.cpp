#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for C: choose bias parameter tC in [-2,2]
    int tC = rnd.next(-2, 2);
    // C in [0,10]
    int C = rnd.wnext(11, tC);

    // Hyper-parameter for K: choose a max bound hiK from common ranges
    vector<int> choicesK = {21, 51, 101, 501, 1001};
    int hiK = rnd.any(choicesK);
    int tK = rnd.next(-2, 2);
    // K in [0, hiK-1], but hiK<=1001 ensures K<=1000
    int K = rnd.wnext(hiK, tK);

    // Hyper-parameter for P: choose a max bound hiP from common ranges
    vector<int> choicesP = {11, 21, 51, 101};
    int hiP = rnd.any(choicesP);
    int tP = rnd.next(-2, 2);
    // P in [0, hiP-1], but hiP<=101 ensures P<=100
    int P = rnd.wnext(hiP, tP);

    // Output one valid test case: C K P
    println(C, K, P);

    return 0;
}
