#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 250, "N");
    inf.readSpace();
    int b = inf.readInt(2, 250, "B");
    inf.readEoln();

    vector<long long> snow(n);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        snow[i] = inf.readLong(0LL, 1000000000LL, "f_i");
    }
    inf.readEoln();
    ensuref(snow.front() == 0, "f_1 must be 0, found %lld", snow.front());
    ensuref(snow.back() == 0, "f_N must be 0, found %lld", snow.back());

    vector<long long> maxDepth(b);
    vector<int> maxStep(b);
    for (int i = 0; i < b; ++i) {
        maxDepth[i] = inf.readLong(0LL, 1000000000LL, "s_i");
        inf.readSpace();
        maxStep[i] = inf.readInt(1, n - 1, "d_i");
        inf.readEoln();
    }
    inf.readEof();

    vector<vector<bool>> reachable(n, vector<bool>(b, false));
    for (int boot = 0; boot < b; ++boot) {
        reachable[0][boot] = true;
    }

    for (int tile = 0; tile < n; ++tile) {
        for (int boot = 0; boot < b; ++boot) {
            if (!reachable[tile][boot] || snow[tile] > maxDepth[boot]) {
                continue;
            }

            for (int next = tile + 1; next < n && next - tile <= maxStep[boot]; ++next) {
                if (snow[next] <= maxDepth[boot]) {
                    reachable[next][boot] = true;
                }
            }

            for (int nextBoot = boot + 1; nextBoot < b; ++nextBoot) {
                if (snow[tile] <= maxDepth[nextBoot]) {
                    reachable[tile][nextBoot] = true;
                }
            }
        }
    }

    bool possible = false;
    for (int boot = 0; boot < b; ++boot) {
        possible = possible || reachable[n - 1][boot];
    }
    ensuref(possible, "input violates guaranteed reachability to tile N");
}
