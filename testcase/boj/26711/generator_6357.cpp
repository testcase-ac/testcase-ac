#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a scenario type with varied probabilities
    int x = rnd.next(0, 9);
    int lenA = 1, lenB = 1;

    if (x == 0) {
        // trivial case
        lenA = lenB = 1;
    } else if (x <= 2) {
        // both very small
        lenA = rnd.next(1, 3);
        lenB = rnd.next(1, 3);
    } else if (x <= 4) {
        // one small, one large
        if (rnd.next(0, 1) == 0) {
            lenA = rnd.next(1, 3);
            lenB = rnd.next(100, 500);
        } else {
            lenA = rnd.next(100, 500);
            lenB = rnd.next(1, 3);
        }
    } else if (x <= 7) {
        // both medium
        lenA = rnd.next(5, 20);
        lenB = rnd.next(5, 20);
    } else if (x == 8) {
        // both large
        lenA = rnd.next(1000, 2000);
        lenB = rnd.next(1000, 2000);
    } else {
        // extreme maximum
        lenA = lenB = 5000;
    }

    // Generate number a
    string a;
    a.reserve(lenA);
    a.push_back(char('1' + rnd.next(0, 8))); // first digit 1-9
    for (int i = 1; i < lenA; i++) {
        a.push_back(char('0' + rnd.next(0, 9)));
    }

    // Generate number b
    string b;
    b.reserve(lenB);
    b.push_back(char('1' + rnd.next(0, 8)));
    for (int i = 1; i < lenB; i++) {
        b.push_back(char('0' + rnd.next(0, 9)));
    }

    // Output the two numbers
    println(a);
    println(b);

    return 0;
}
