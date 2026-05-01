#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int Q = rnd.next(8, 10);
    println(Q);
    for (int i = 0; i < Q; i++) {
        int tp = rnd.next(0, 7);
        long long W, B;
        switch (tp) {
            case 0:
                W = rnd.next(1, 5);
                B = rnd.next(1, 5);
                break;
            case 1:
                W = rnd.next(1, 5);
                B = rnd.next(6, 20);
                break;
            case 2:
                W = rnd.next(6, 20);
                B = rnd.next(1, 5);
                break;
            case 3:
                W = rnd.next(6, 20);
                B = rnd.next(6, 20);
                break;
            case 4:
                W = rnd.next(1, 20);
                B = W;
                break;
            case 5:
                W = rnd.next(20, 50);
                B = rnd.next(1, 3);
                break;
            case 6:
                W = 1;
                B = rnd.next(1, 10);
                break;
            case 7:
                W = rnd.next(1, 50);
                B = 1;
                break;
            default:
                W = rnd.next(1, 10);
                B = rnd.next(1, 10);
        }
        println(W, B);
    }
    return 0;
}
