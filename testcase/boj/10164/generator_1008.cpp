#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int N, M;
    N = rnd.next(1, 5);
    if (N == 1) {
        M = rnd.next(2, 5);
    } else {
        M = rnd.next(1, 5);
    }
    
    int total_cells = N * M;
    int K;
    
    if (total_cells <= 2) {
        K = 0;
    } else {
        bool include_k = rnd.next(0, 1);
        if (include_k) {
            K = rnd.next(2, total_cells - 1);
        } else {
            K = 0;
        }
    }
    
    println(N, M, K);
}
