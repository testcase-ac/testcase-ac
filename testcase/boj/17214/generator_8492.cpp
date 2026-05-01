#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    bool hasX = false, hasC = false;
    int a = 0; // coefficient of x
    int c = 0; // constant term

    int type = rnd.next(0, 9);

    switch (type) {
        case 0: { // only positive x term, small
            hasX = true;
            int mag = rnd.next(1, 5); // 2..10
            a = 2 * mag;
            break;
        }
        case 1: { // only negative x term, small
            hasX = true;
            int mag = rnd.next(1, 5);
            a = -2 * mag;
            break;
        }
        case 2: { // only positive constant, small
            hasC = true;
            int mag = rnd.next(1, 20);
            c = mag;
            break;
        }
        case 3: { // only negative constant, small
            hasC = true;
            int mag = rnd.next(1, 20);
            c = -mag;
            break;
        }
        case 4: { // 2x + positive constant
            hasX = hasC = true;
            a = 2;
            int mag = rnd.next(1, 20);
            c = mag;
            break;
        }
        case 5: { // 2x - positive constant
            hasX = hasC = true;
            a = 2;
            int mag = rnd.next(1, 20);
            c = -mag;
            break;
        }
        case 6: { // -2x + positive constant
            hasX = hasC = true;
            a = -2;
            int mag = rnd.next(1, 20);
            c = mag;
            break;
        }
        case 7: { // -2x - positive constant
            hasX = hasC = true;
            a = -2;
            int mag = rnd.next(1, 20);
            c = -mag;
            break;
        }
        case 8: { // extreme |a|, optional constant
            hasX = true;
            int mag = rnd.next(2500, 5000); // 5000..10000
            a = (rnd.next(0, 1) ? 1 : -1) * 2 * mag;
            hasC = (rnd.next(0, 1) == 1);
            if (hasC) {
                // mostly small constant, sometimes large
                if (rnd.next(0, 4) == 0) {
                    int cmag = rnd.next(1, 10000);
                    c = (rnd.next(0, 1) ? 1 : -1) * cmag;
                } else {
                    int cmag = rnd.next(1, 20);
                    c = (rnd.next(0, 1) ? 1 : -1) * cmag;
                }
            }
            break;
        }
        case 9: { // extreme constant, optional x term
            hasC = true;
            int cmag;
            if (rnd.next(0, 1)) {
                cmag = 10000;
            } else {
                cmag = rnd.next(5000, 10000);
            }
            c = (rnd.next(0, 1) ? 1 : -1) * cmag;

            hasX = (rnd.next(0, 1) == 1);
            if (hasX) {
                if (rnd.next(0, 1) == 0) {
                    // small a, including 2 to test division -> 1
                    int mag = rnd.next(1, 5);
                    a = (rnd.next(0, 1) ? 1 : -1) * 2 * mag;
                } else {
                    // large a
                    int mag = rnd.next(2500, 5000);
                    a = (rnd.next(0, 1) ? 1 : -1) * 2 * mag;
                }
            }
            break;
        }
    }

    // Safety: ensure we have at least one term
    if (!hasX && !hasC) {
        hasX = true;
        a = 2;
    }

    string s;

    if (hasX) {
        if (a == 1) {
            s += "x";
        } else if (a == -1) {
            s += "-x";
        } else {
            s += to_string(a) + "x";
        }
    }

    if (hasC) {
        if (s.empty()) {
            s += to_string(c);
        } else {
            if (c > 0) {
                s += "+" + to_string(c);
            } else {
                s += to_string(c); // includes '-'
            }
        }
    }

    println(s);
    return 0;
}
