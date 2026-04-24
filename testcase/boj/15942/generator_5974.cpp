#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate N with a bias: small, medium, or large
    int bias = rnd.next(-2, 2); // negative biases small, positive biases large
    int N = rnd.wnext(200000, bias) + 1;
    if (N == 1) {
        // Only one element: trivial case
        println(1);
        println(1, 1);
        return 0;
    }

    // Choose among several scenarios to catch edge cases
    // type 0: trivial possible (root, k=1)
    // type 1: impossible because smallest element cannot go off-root
    // type 2: possible placing max in a leaf
    // type 3: impossible placing max in an internal node
    // type 4: fully random k,p
    int type = rnd.next(4);
    int k, p;
    int half = N / 2;

    switch (type) {
        case 0:
            // trivial possible: k=1 at root
            k = 1;
            p = 1;
            break;
        case 1:
            // impossible: smallest can't go off-root
            k = 1;
            p = rnd.next(2, N);
            break;
        case 2:
            // possible: largest can go to any leaf
            k = N;
            p = rnd.next(half + 1, N);
            break;
        case 3:
            // impossible: largest cannot stay in an internal node
            k = N;
            p = rnd.next(1, half);
            break;
        default:
            // general random case
            k = rnd.next(1, N);
            p = rnd.next(1, N);
            break;
    }

    // Output in the required format
    println(N);
    println(k, p);

    return 0;
}
