#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 6);
    int K = rnd.next(1, 2*N);
    int w = rnd.next(-2, 2);
    int mn = rnd.next(1, 9), mx = rnd.next(mn, 9);
    println(N, K);
    vector<int> v;
    for(int i = 0; i < 2*N; i++) {
        v.push_back(rnd.wnext(mn, mx, w));
    }
    println(v);
}
