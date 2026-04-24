#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter to bias length toward small or large
    int t = rnd.next(-2, 2);
    int N = rnd.wnext(15, t) + 1;  // length in [1..15]
    // Limit alphabet to a random prefix of A..Z
    int charMax = rnd.next(0, 25);
    // Probability to repeat an existing character
    double repProb = rnd.next();

    string s;
    s.reserve(N);
    for (int i = 0; i < N; i++) {
        if (i > 0 && rnd.next() < repProb) {
            // reuse a previous character
            s.push_back(rnd.any(s));
        } else {
            // new random character in [A..A+charMax]
            s.push_back(char('A' + rnd.next(0, charMax)));
        }
    }

    println(s);
    return 0;
}
