#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 9);
    int MN = rnd.next(-10, 0);
    int MX = rnd.next(1, 10);
    println(N);
    for (int i = 0; i < N; i++) {
        cout << rnd.next(MN, MX);
        if (i != N - 1) cout << " ";
    }
    cout << endl;
    return 0;
}
