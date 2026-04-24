#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Ensure number of notes >= 6 so that string numbers 1..6 are valid under validator
    int N = rnd.next(6, 10);
    int P = rnd.next(2, 20);
    // Hyper-parameters for movement patterns
    double pUp = rnd.next(0.0, 1.0);
    double pDown = rnd.next(0.0, 1.0 - pUp);
    double pSwitch = rnd.next(0.0, 1.0);

    vector<pair<int,int>> notes;
    // Initial note
    int currStr = rnd.next(1, 6);
    int currFret = rnd.next(1, P);
    notes.emplace_back(currStr, currFret);

    // Generate melody
    for (int i = 1; i < N; i++) {
        int s, f;
        if (rnd.next() < pSwitch) {
            // Switch to a random string and fret
            s = rnd.next(1, 6);
            f = rnd.next(1, P);
        } else {
            // Stay on same string, adjust frets
            s = currStr;
            double r = rnd.next();
            if (r < pUp && currFret < P) {
                // move up
                f = rnd.next(currFret, P);
            } else if (r < pUp + pDown && currFret > 1) {
                // move down
                f = rnd.next(1, currFret);
            } else {
                // random fret
                f = rnd.next(1, P);
            }
        }
        currStr = s;
        currFret = f;
        notes.emplace_back(s, f);
    }

    // Output
    println(N, P);
    for (auto &pr : notes)
        println(pr.first, pr.second);

    return 0;
}
