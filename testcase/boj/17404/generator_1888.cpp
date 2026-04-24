#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 8);
    int mn = 1, mx = 30;
    println(N);
    for(int i = 0; i < N; i++) {
        int local_mn = rnd.next(mn, mx), local_mx = rnd.next(local_mn, mx);
        println(rnd.next(local_mn, local_mx), rnd.next(local_mn, local_mx), rnd.next(local_mn, local_mx));
    }
}
