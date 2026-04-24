#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 10);
    println(n, m);
    
    for(int k = 0; k < m; k++) {
        int i = rnd.next(1, n);
        int j = rnd.next(i, n);
        println(i, j);
    }
}
