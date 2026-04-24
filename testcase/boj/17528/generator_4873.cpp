#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of tasks
    int n = rnd.next(1, 10);
    // Hyper-parameters for skewed and equal tasks
    double skewProb = rnd.next(0.0, 1.0);
    double eqProb   = rnd.next(0.0, 1.0);

    vector<pair<int,int>> tasks;
    for (int i = 0; i < n; i++) {
        double u = rnd.next();
        if (u < eqProb) {
            // Equal times
            int x = rnd.next(1, 20);
            tasks.emplace_back(x, x);
        } else if (u < eqProb + skewProb) {
            // Skewed tasks
            if (rnd.next() < 0.5) {
                // Prefer A: small a, large b
                int a = rnd.next(1, 5);
                int b = rnd.next(6, 20);
                tasks.emplace_back(a, b);
            } else {
                // Prefer B: large a, small b
                int a = rnd.next(6, 20);
                int b = rnd.next(1, 5);
                tasks.emplace_back(a, b);
            }
        } else {
            // Balanced random times
            int a = rnd.next(1, 20);
            int b = rnd.next(1, 20);
            tasks.emplace_back(a, b);
        }
    }

    // Randomize order of tasks
    shuffle(tasks.begin(), tasks.end());

    // Output
    println(n);
    for (auto &p : tasks)
        println(p.first, p.second);

    return 0;
}
