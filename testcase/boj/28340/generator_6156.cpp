#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Prepare 7 diverse test cases
    vector<int> types = {0,1,2,3,4,5,6};
    shuffle(types.begin(), types.end());
    int T = rnd.next(1, 3);
    println(T);
    for (int t=0; t<T; t++) {
        int tp = rnd.any(types);
        int N, K;
        vector<int> C;
        switch (tp) {
            case 0:
                // all zero frequencies
                N = 2; K = 2;
                C = {0, 0};
                break;
            case 1:
                // small N=2, K>2
                N = 2; K = rnd.next(3, 10);
                C.resize(N);
                for (int i = 0; i < N; i++) C[i] = rnd.next(1, 10);
                break;
            case 2:
                // binary Huffman with zeros
                N = rnd.next(3, 7); K = 2;
                C.resize(N);
                for (int i = 0; i < N; i++) C[i] = rnd.next(0, 20);
                break;
            case 3:
                // medium N, small K
                N = rnd.next(4, 10); K = rnd.next(3, 5);
                C.resize(N);
                for (int i = 0; i < N; i++) C[i] = rnd.next(0, 30);
                break;
            case 4:
                // K >= N, forces shallow tree
                N = rnd.next(5, 10); K = rnd.next(N, N + 5);
                C.resize(N);
                for (int i = 0; i < N; i++) C[i] = rnd.next(1, 50);
                break;
            case 5:
                // random frequencies and K,N
                N = rnd.next(3, 8); K = rnd.next(3, 8);
                C.resize(N);
                for (int i = 0; i < N; i++) C[i] = rnd.next(0, 100);
                break;
            default:
                // ensure padding needed: (N-1)%(K-1)!=0
                do {
                    N = rnd.next(3, 10);
                    K = rnd.next(2, 10);
                } while ((N - 1) % (K - 1) == 0);
                C.resize(N);
                for (int i = 0; i < N; i++) C[i] = rnd.next(0, 20);
                break;
        }
        // Output this test case
        println(N, K);
        println(C);
    }
    return 0;
}
