#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // small number of cards
    int n = rnd.next(3, 10);

    // hyper-parameters for distribution of negatives, zeros, positives
    int wneg = rnd.next(1, 10);
    int wzero = rnd.next(1, 10);
    int wpos = rnd.next(1, 10);
    // shape parameters for magnitude bias
    int shapeNeg = rnd.next(-2, 2);
    int shapePos = rnd.next(-2, 2);

    vector<int> a;
    a.reserve(n);
    int totalW = wneg + wzero + wpos;
    for (int i = 0; i < n; i++) {
        int t = rnd.next(totalW - 1);
        if (t < wneg) {
            // negative number with biased magnitude
            int mag = rnd.wnext(1000, shapeNeg) + 1;
            a.push_back(-mag);
        } else if (t < wneg + wzero) {
            // zero
            a.push_back(0);
        } else {
            // positive number with biased magnitude
            int mag = rnd.wnext(1000, shapePos) + 1;
            a.push_back(mag);
        }
    }

    // occasional duplicate to test handling of identical cards
    if (rnd.next(0, 1)) {
        int i = rnd.next(0, n - 1);
        int j = rnd.next(0, n - 1);
        a[j] = a[i];
    }

    // shuffle the order of cards
    shuffle(a.begin(), a.end());

    // output
    println(n);
    println(a);

    return 0;
}
