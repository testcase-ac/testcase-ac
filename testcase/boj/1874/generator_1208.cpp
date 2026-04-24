#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 8);
    println(N);
    vector<int> perm(N);
    for(int i=0; i<N; i++) {
        perm[i] = i+1;
    }
    shuffle(perm.begin(), perm.end());
    for(int i=0; i<N; i++) {
        println(perm[i]);
    }
}
