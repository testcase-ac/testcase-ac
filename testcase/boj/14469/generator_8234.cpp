#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N: small, medium, or larger but readable
    int modeN = rnd.next(0, 2);
    int N;
    if (modeN == 0) {
        N = rnd.next(1, 5);
    } else if (modeN == 1) {
        N = rnd.next(6, 15);
    } else {
        N = rnd.next(16, 30);
    }
    // Hyper-parameter for arrival times
    int modeA = rnd.next(0, 2);
    vector<int> arr(N);
    if (modeA == 0) {
        // Uniform over full range
        for (int i = 0; i < N; i++)
            arr[i] = rnd.next(1, 1000000);
    } else if (modeA == 1) {
        // Cluster around a center
        int center = rnd.next(1, 1000000);
        for (int i = 0; i < N; i++) {
            int delta = rnd.next(-1000, 1000);
            int v = center + delta;
            if (v < 1) v = 1;
            if (v > 1000000) v = 1000000;
            arr[i] = v;
        }
    } else {
        // Arithmetic progression with possible clamp
        int start = rnd.next(1, 1000000);
        int diff = rnd.next(0, 1000);
        for (int i = 0; i < N; i++) {
            long long v = start + 1LL * diff * i;
            if (v > 1000000) v = 1000000;
            arr[i] = int(v);
        }
    }
    sort(arr.begin(), arr.end());
    // Hyper-parameter for processing times
    int modeP = rnd.next(0, 2);
    vector<int> proc(N);
    for (int i = 0; i < N; i++) {
        if (modeP == 0)
            proc[i] = rnd.next(1, 10);
        else if (modeP == 1)
            proc[i] = rnd.next(1, 1000000);
        else
            proc[i] = rnd.next(1, 1000);
    }
    // Combine and shuffle to create arbitrary input order
    vector<pair<int,int>> cows;
    for (int i = 0; i < N; i++)
        cows.emplace_back(arr[i], proc[i]);
    shuffle(cows.begin(), cows.end());
    // Output
    println(N);
    for (auto &c : cows)
        println(c.first, c.second);
    return 0;
}
