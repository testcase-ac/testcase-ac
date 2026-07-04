#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int A = rnd.next(0, 23);
    int B = rnd.next(0, 59);
    int C = rnd.next(0, 1000);

    if (mode == 0) {
        C = 0;
    } else if (mode == 1) {
        B = rnd.next(50, 59);
        C = rnd.next(1, 20);
    } else if (mode == 2) {
        A = rnd.next(20, 23);
        B = rnd.next(0, 59);
        C = rnd.next(60, 240);
    } else if (mode == 3) {
        A = rnd.next(0, 23);
        B = rnd.next(0, 59);
        C = rnd.next(720, 1000);
    } else if (mode == 4) {
        A = rnd.any(vector<int>{0, 23});
        B = rnd.any(vector<int>{0, 59});
        C = rnd.any(vector<int>{1, 59, 60, 61, 999, 1000});
    }

    println(A, B);
    println(C);
    return 0;
}
