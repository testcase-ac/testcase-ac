#include "testlib.h"
#include <vector>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 8);
    println(N);
    for(int i=0; i<N-1; i++) {
        cout << rnd.next(1, 8);
        if(i != N-2) {
            cout << " ";
        }
    }
    cout << '\n';
    for(int i=0; i<N; i++) {
        cout << rnd.next(1, 8);
        if(i != N-1) {
            cout << " ";
        }
    }
    cout << '\n';
}
