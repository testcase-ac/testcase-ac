#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N = rnd.next(1, 5);          // number of multitap holes
    int K = rnd.next(1, 20);         // total usage count
    int maxD = min(K, 10);
    int D = rnd.next(1, maxD);       // number of distinct devices (1..D)

    // Prepare device IDs 1..D
    vector<int> devices(D);
    for (int i = 0; i < D; ++i) {
        devices[i] = i + 1;
    }

    // Generate the usage sequence according to one of three styles
    vector<int> seq;
    int style = rnd.next(1, 3);
    if (style == 1) {
        // Cyclic usage: 1,2,...,D,1,2,...
        for (int i = 0; i < K; ++i) {
            seq.push_back(devices[i % D]);
        }
    } else if (style == 2) {
        // Fully random picks among devices
        for (int i = 0; i < K; ++i) {
            seq.push_back(rnd.any(devices));
        }
    } else {
        // Burst style: pick a device, use it 1-3 times consecutively
        int i = 0;
        while (i < K) {
            int d = rnd.any(devices);
            int run = rnd.next(1, 3);
            for (int t = 0; t < run && i < K; ++t) {
                seq.push_back(d);
                ++i;
            }
        }
    }

    // Output in the required format
    println(N, K);
    println(seq);

    return 0;
}
