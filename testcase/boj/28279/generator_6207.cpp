#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of commands between small and medium for manual checking
    int N = rnd.next(5, 20);
    // Hyperparameter: bias for command distribution
    int tBias = rnd.next(-2, 2);
    // Hyperparameter: upper bound for pushed values
    int Xmax = rnd.next(1, 100000);

    vector<pair<int,int>> ops;
    ops.reserve(N);

    // Generate N-1 random commands with bias
    for (int i = 0; i < N - 1; i++) {
        int cmd = rnd.wnext(8, tBias) + 1; // 1..8
        if (cmd == 1 || cmd == 2) {
            int x = rnd.next(1, Xmax);
            ops.emplace_back(cmd, x);
        } else {
            ops.emplace_back(cmd, 0);
        }
    }
    // Ensure at least one output command at the end
    int lastCmd = rnd.next(3, 8);
    ops.emplace_back(lastCmd, 0);

    // Output
    println((int)ops.size());
    for (auto &p : ops) {
        if (p.first == 1 || p.first == 2)
            println(p.first, p.second);
        else
            println(p.first);
    }
    return 0;
}
