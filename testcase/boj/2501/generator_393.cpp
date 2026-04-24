#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    double r = rnd.next();
    if(r < 0.5) {
        int N = rnd.next(1, 25);
        int K = rnd.next(1, N);
        println(N, K);
    } else {
        int N = rnd.next(1, 10000);
        int K = rnd.next(1, N);
        println(N, K);
    }
}
