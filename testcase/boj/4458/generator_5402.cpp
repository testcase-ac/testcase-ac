#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of lines
    int N = rnd.next(1, 10);
    println(N);
    // Hyper-parameters for character distribution
    int wAlpha = rnd.next(1, 5);
    int wSpace = rnd.next(0, wAlpha);
    int wHyph = rnd.next(0, wAlpha);
    double firstLowerProb = rnd.next();
    int totalW = wAlpha + wSpace + wHyph;
    for (int i = 0; i < N; i++) {
        int L = rnd.next(1, 30);
        string s;
        s.reserve(L);
        // First character: always alphabetic
        if (rnd.next() < firstLowerProb) {
            s.push_back(char('a' + rnd.next(0, 25)));
        } else {
            s.push_back(char('A' + rnd.next(0, 25)));
        }
        // Remaining characters
        for (int j = 1; j < L; j++) {
            int x = rnd.next(0, totalW - 1);
            if (x < wAlpha) {
                // alphabetic
                if (rnd.next() < 0.5)
                    s.push_back(char('a' + rnd.next(0, 25)));
                else
                    s.push_back(char('A' + rnd.next(0, 25)));
            } else if (x < wAlpha + wSpace) {
                s.push_back(' ');
            } else {
                s.push_back('-');
            }
        }
        println(s);
    }
    return 0;
}
