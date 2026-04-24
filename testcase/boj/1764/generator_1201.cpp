#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<string> names;
    int N = rnd.next(2, 10);
    for(int i=0; i<N; i++) {
        string name = rnd.next("[a-e]{1,3}");
        while(find(names.begin(), names.end(), name) != names.end()) {
            name = rnd.next("[a-e]{1,3}");
        }
        names.push_back(name);
    }
    int A = rnd.next(1, N), B = rnd.next(1, N);
    vector<int> perm(N);
    for(int i=0; i<N; i++) {
        perm[i] = i;
    }
    shuffle(perm.begin(), perm.end());
    vector<string> av, bv;
    for(int i=0; i<A; i++) {
        av.push_back(names[perm[i]]);
    }
    for(int i=0; i<B; i++) {
        bv.push_back(names[perm[i]]);
    }
    shuffle(av.begin(), av.end());
    shuffle(bv.begin(), bv.end());
    println(A, B);
    for(int i=0; i<A; i++) {
        println(av[i]);
    }
    for(int i=0; i<B; i++) {
        println(bv[i]);
    }
}
