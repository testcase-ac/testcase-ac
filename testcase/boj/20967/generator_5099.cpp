#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int n = rnd.next(1, 20);                     // length of the heard string
    char maxC = char(rnd.next(int('a'), int('z'))); // highest letter used
    double resetProb = rnd.next(0.0, 1.0);        // probability to "reset" and potentially start a new cycle

    string s;
    s.reserve(n);
    for (int i = 0; i < n; i++) {
        char c;
        if (i == 0 || rnd.next() < resetProb) {
            // choose any letter from 'a' to maxC
            c = char(rnd.next(int('a'), int(maxC)));
        } else {
            // choose a letter not less than the previous to continue current cycle
            c = char(rnd.next(int(s.back()), int(maxC)));
        }
        s.push_back(c);
    }

    // Output the generated heard string
    println(s);

    return 0;
}
