#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int pairs = rnd.next(1, 16);
    if (mode == 5) {
        pairs = rnd.next(20, 80);
    }

    vector<string> pairChoices = {"GG", "HH", "GH", "HG"};
    string cows;
    cows.reserve(2 * pairs);

    for (int i = 0; i < pairs; ++i) {
        string p;
        if (mode == 0) {
            p = pairChoices[rnd.next(0, 3)];
        } else if (mode == 1) {
            p = (i % 2 == 0 ? "GH" : "HG");
            if (rnd.next(0, 4) == 0) p = pairChoices[rnd.next(0, 3)];
        } else if (mode == 2) {
            p = (rnd.next(0, 1) == 0 ? "GG" : "HH");
        } else if (mode == 3) {
            p = (rnd.next(0, 2) == 0 ? "GH" : "GG");
        } else if (mode == 4) {
            p = (rnd.next(0, 2) == 0 ? "HG" : "HH");
        } else {
            p = (rnd.next(0, 99) < 45 ? "GH" : (rnd.next(0, 1) == 0 ? "GG" : "HH"));
        }
        cows += p;
    }

    if (rnd.next(0, 3) == 0) {
        for (char& c : cows) {
            c = (c == 'G' ? 'H' : 'G');
        }
    }

    println((int)cows.size());
    println(cows);
    return 0;
}
