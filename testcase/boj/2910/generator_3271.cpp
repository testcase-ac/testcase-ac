#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameters for diversity
    int N = rnd.next(1, 10);              // sequence length
    int maxElement = rnd.next(1, 20);     // maximum possible value in sequence
    int C = rnd.next(maxElement, 100);    // C >= max element

    // Number of distinct values in the sequence
    int K = rnd.next(1, min(N, maxElement));

    // Choose K distinct values from [1..maxElement]
    vector<int> domain(maxElement);
    for (int i = 0; i < maxElement; i++)
        domain[i] = i + 1;
    shuffle(domain.begin(), domain.end());
    vector<int> values(domain.begin(), domain.begin() + K);

    // Partition N into K positive frequencies via random cuts
    vector<int> freq(K);
    if (K == 1) {
        freq[0] = N;
    } else {
        vector<int> cuts;
        // Domain for cuts is [1..N-1]
        vector<int> cutDomain(N - 1);
        for (int i = 0; i < N - 1; i++)
            cutDomain[i] = i + 1;
        shuffle(cutDomain.begin(), cutDomain.end());
        cuts.assign(cutDomain.begin(), cutDomain.begin() + (K - 1));
        sort(cuts.begin(), cuts.end());
        // First segment
        freq[0] = cuts[0];
        // Middle segments
        for (int i = 1; i < K - 1; i++)
            freq[i] = cuts[i] - cuts[i-1];
        // Last segment
        freq[K-1] = N - cuts[K-2];
    }

    // Build the sequence according to frequencies
    vector<int> seq;
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < freq[i]; j++)
            seq.push_back(values[i]);
    }

    // Sometimes keep blocks, sometimes fully shuffle
    if (rnd.next() < 0.5) {
        shuffle(seq.begin(), seq.end());
    }

    // Output
    println(N, C);
    println(seq);

    return 0;
}
