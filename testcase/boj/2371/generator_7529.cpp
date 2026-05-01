#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of files
    int N = rnd.next(2, 8);
    vector<vector<int>> seqs;

    // Create a cluster of sequences sharing a common prefix
    int clusterSize = rnd.next(2, min(5, N));
    int pLen = rnd.next(1, 3);
    vector<int> prefix(pLen);
    for (int i = 0; i < pLen; i++) {
        prefix[i] = rnd.next(1, 100);
    }
    for (int i = 0; i < clusterSize; i++) {
        vector<int> seq = prefix;
        // Diverge at next position
        seq.push_back(rnd.next(1, 100));
        // Optional extra suffix
        int extra = rnd.next(0, 3);
        for (int j = 0; j < extra; j++) {
            seq.push_back(rnd.next(1, 100));
        }
        seqs.push_back(seq);
    }

    // Generate remaining sequences, ensuring uniqueness
    while ((int)seqs.size() < N) {
        int len = rnd.next(1, 6);
        vector<int> seq(len);
        for (int i = 0; i < len; i++) {
            seq[i] = rnd.next(1, 100);
        }
        bool dup = false;
        for (auto &os : seqs) {
            if (os == seq) { dup = true; break; }
        }
        if (!dup) seqs.push_back(seq);
    }

    // Shuffle the order of files
    shuffle(seqs.begin(), seqs.end());

    // Output
    println(N);
    for (auto &seq : seqs) {
        vector<int> tmp = seq;
        tmp.push_back(-1);
        println(tmp);
    }
    return 0;
}
