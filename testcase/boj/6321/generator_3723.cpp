#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of computer names
    int n = rnd.next(1, 10);
    println(n);

    for (int i = 0; i < n; i++) {
        // Length of this name
        int len = rnd.next(1, 10);

        string s;
        // 10% chance to generate a string of all 'Z's (tests Z->A wrap)
        if (rnd.next() < 0.1) {
            s = string(len, 'Z');
        } else {
            // 50% chance to bias towards 'Z'
            bool biasZ = rnd.next() < 0.5;
            for (int j = 0; j < len; j++) {
                if (biasZ) {
                    // 30% of the time pick 'Z', otherwise A-Y
                    if (rnd.next() < 0.3)
                        s += 'Z';
                    else
                        s += char('A' + rnd.next(0, 24)); // 'A'..'Y'
                } else {
                    // uniform 'A'..'Z'
                    s += char('A' + rnd.next(0, 25));
                }
            }
        }
        println(s);
    }
    return 0;
}
