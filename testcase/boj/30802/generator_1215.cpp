#include "testlib.h"
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<int> A(6);
    vector<int> cands = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    shuffle(cands.begin(), cands.end());
    int cands_size = rnd.next(1, 9);
    if(cands_size == 1 && cands[0] == 0) {
        cands_size = 2;
    }
    cands.erase(cands.begin()+cands_size, cands.end());

    int N = 0;
    while(N < 1) {
        for(int i=0; i<6; i++) {
            A[i] = cands[rnd.next(0, (int)cands.size()-1)];
        }
        N = accumulate(A.begin(), A.end(), 0ll);
    }

    println(N);
    println(A);
    int T = rnd.next(2, N+1), P = rnd.next(2, N+1);
    println(T, P);
}
