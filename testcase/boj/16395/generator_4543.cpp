#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter to bias n towards small or large values
    int t_n = rnd.next(-2, 2);
    int n = rnd.wnext(30, t_n) + 1;  // n in [1,30]
    // Hyper-parameter to bias k towards edges or middle
    int t_k = rnd.next(-2, 2);
    int k = rnd.wnext(n, t_k) + 1;   // k in [1,n]
    println(n, k);
    return 0;
}
