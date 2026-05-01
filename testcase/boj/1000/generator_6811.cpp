#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int A, B;

    A = rnd.next(1, 8);
    B = rnd.next(1, 9);

    println(A, B);
    return 0;
}
