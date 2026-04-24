#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 9);
    int MX = rnd.next(2, 9);
    println(N);
    for (int i = 0; i < N; i++) {
        cout << rnd.next(1, MX);
        if (i < N - 1) cout << " ";
    }
    cout << endl;
}
