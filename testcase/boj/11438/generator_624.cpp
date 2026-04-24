#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int N = rnd.next(2, 10);
    println(N);
    
    for (int i = 2; i <= N; i++) {
        int parent = rnd.next(1, i - 1);
        println(parent, i);
    }
    
    int M = rnd.next(1, 10);
    println(M);
    
    for (int i = 0; i < M; i++) {
        int u = rnd.next(1, N);
        int v = rnd.next(1, N);
        println(u, v);
    }
}
