#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: probability of picking 'N'/'n'
    double targetProb = rnd.next();  // [0,1)
    bool pickTarget = rnd.next() < targetProb;

    char c;
    if (pickTarget) {
        // Choose between 'N' and 'n'
        c = rnd.next() < 0.5 ? 'N' : 'n';
    } else {
        // Hyper-parameter: probability of uppercase vs lowercase for non-target
        double upperProb = rnd.next();
        if (rnd.next() < upperProb) {
            // Uppercase letter excluding 'N'
            do {
                c = char(rnd.next('A', 'Z'));
            } while (c == 'N');
        } else {
            // Lowercase letter excluding 'n'
            do {
                c = char(rnd.next('a', 'z'));
            } while (c == 'n');
        }
    }

    // Output a single character
    printf("%c\n", c);

    return 0;
}
