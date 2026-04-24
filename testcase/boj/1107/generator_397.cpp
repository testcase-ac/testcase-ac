#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(0, 500000);
    if(rnd.next() < 0.5) {
        N = rnd.next(0, 500);
    }
    println(N);
    int M = rnd.next(0, 10);
    println(M);
    vector<int> v(10);
    iota(v.begin(), v.end(), 0);
    shuffle(v.begin(), v.end());
    if(M) {
        for(int i=0; i<M; i++) {
            cout << v[i];
            if(i == M-1) {
                cout << endl;
            } else {
                cout << ' ';
            }
        }
    }
}
