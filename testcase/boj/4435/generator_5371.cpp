#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);

    vector<int> tBias = {-2, -1, 0, 1, 2};
    for (int tc = 0; tc < T; tc++) {
        // Generate Good side counts (6 species)
        vector<int> good(6, 0);
        int tGood = rnd.wnext(11, rnd.any(tBias)); // total units [0,10], biased
        if (rnd.next() < 0.3) {
            // single-species heavy case
            int idx = rnd.next(5);
            int cnt = rnd.next(0, 10);
            good[idx] = cnt;
        } else {
            // distribute tGood units randomly among species
            for (int i = 0; i < tGood; i++) {
                good[rnd.next(5)]++;
            }
        }

        // Generate Evil side counts (7 species)
        vector<int> evil(7, 0);
        int tEvil = rnd.wnext(11, rnd.any(tBias)); // total units [0,10], biased
        if (rnd.next() < 0.3) {
            int idx = rnd.next(6);
            int cnt = rnd.next(0, 10);
            evil[idx] = cnt;
        } else {
            for (int i = 0; i < tEvil; i++) {
                evil[rnd.next(6)]++;
            }
        }

        // Output the two lines for this battle
        println(good);
        println(evil);
    }

    return 0;
}
