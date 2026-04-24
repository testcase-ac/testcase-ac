#include "testlib.h"
#include <vector>
#include <array>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter 1: size of arrays
    int n = rnd.next(1, 10);

    // Hyper-parameter 2: choose value distribution type
    // 0 = small [-10,10], 1 = medium [-1000,1000], 2 = wide full range, 3 = biased zeros
    int valType = rnd.next(0, 3);

    // Hyper-parameter 3: probability to duplicate the previous row
    double dupProb = rnd.next(0.0, 1.0);

    vector<array<int,4>> rows;
    rows.reserve(n);

    for (int i = 0; i < n; i++) {
        array<int,4> row;
        if (i > 0 && rnd.next() < dupProb) {
            // duplicate previous row
            row = rows.back();
        } else {
            // generate new row according to valType
            for (int j = 0; j < 4; j++) {
                if (valType == 0) {
                    row[j] = rnd.next(-10, 10);
                } else if (valType == 1) {
                    row[j] = rnd.next(-1000, 1000);
                } else if (valType == 2) {
                    row[j] = rnd.next(-(1<<28), (1<<28));
                } else {
                    // biased zeros: half zeros, half in [-100,100]
                    if (rnd.next() < 0.5)
                        row[j] = 0;
                    else
                        row[j] = rnd.next(-100, 100);
                }
            }
        }
        rows.push_back(row);
    }

    // Output in the required format
    println(n);
    for (auto &r : rows) {
        println(r[0], r[1], r[2], r[3]);
    }

    return 0;
}
