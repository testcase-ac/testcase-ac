#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    double p = rnd.next();
    int N;
    if (p < 0.1) {
        N = 1;
    } else if (p < 0.2) {
        N = 100;
    } else if (p < 0.35) {
        N = 20;
    } else if (p < 0.5) {
        N = 21;
    } else if (p < 0.75) {
        N = rnd.next(2, 19);
    } else {
        N = rnd.next(22, 99);
    }
    println(N);
    return 0;
}
