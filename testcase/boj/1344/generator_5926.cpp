#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int A, B;
    int t = rnd.next(0, 5);
    switch (t) {
        case 0:
            // fully random probabilities
            A = rnd.next(0, 100);
            B = rnd.next(0, 100);
            break;
        case 1:
            // both low probabilities
            A = rnd.next(0, 30);
            B = rnd.next(0, 30);
            break;
        case 2:
            // both high probabilities
            A = rnd.next(70, 100);
            B = rnd.next(70, 100);
            break;
        case 3:
            // A low, B high
            A = rnd.next(0, 30);
            B = rnd.next(70, 100);
            break;
        case 4:
            // A high, B low
            A = rnd.next(70, 100);
            B = rnd.next(0, 30);
            break;
        case 5:
            // equal probabilities
            A = rnd.next(0, 100);
            B = A;
            break;
    }
    println(A);
    println(B);
    return 0;
}
