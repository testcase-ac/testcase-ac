#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int t1 = rnd.next(-2, 2);
    int m = rnd.wnext(10, t1) + 1;           // number of men [1..10]
    int t2 = rnd.next(-2, 2);
    int f = rnd.wnext(10, t2) + 1;           // number of women [1..10]

    int maxRooms = min(m + f, 10);
    int t3 = rnd.next(-2, 2);
    int r = rnd.wnext(maxRooms, t3) + 1;     // number of rooms [1..min(m+f,10)]

    int maxC = min(m, f);
    int t4 = rnd.next(-2, 2);
    int c = rnd.wnext(maxC + 1, t4);        // number of couples [0..maxC]

    // Output header
    println(m, f, r, c);

    // Rooms: capacity a in [1..5], cost b in [1..100]
    for (int i = 0; i < r; i++) {
        int a = rnd.next(1, 5);
        int t5 = rnd.next(-2, 2);
        int b = rnd.wnext(100, t5) + 1;
        println(a, b);
    }
    return 0;
}
