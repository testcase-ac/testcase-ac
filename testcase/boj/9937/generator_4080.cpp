#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of lines
    int N = rnd.next(1, 10);
    // Number of parallel families
    int K = rnd.next(1, N);
    // Partition N into K positive sizes
    vector<int> sizes(K, 1);
    int extra = N - K;
    while (extra > 0) {
        int i = rnd.next(0, K-1);
        sizes[i]++;
        extra--;
    }
    // Generate direction normals for each family
    set<pair<int,int>> used_dirs;
    vector<pair<pair<int,int>, vector<int>>> families; // ((A,B), list of Cs)
    for (int i = 0; i < K; i++) {
        int A, B;
        // pick some horizontals/verticals/general for diversity
        double p = rnd.next();
        if (p < 0.3) {
            A = 0; B = 1;
        } else if (p < 0.6) {
            A = 1; B = 0;
        } else {
            // general direction
            do {
                A = rnd.next(-5, 5);
                B = rnd.next(-5, 5);
            } while (A == 0 && B == 0);
            int g = gcd(abs(A), abs(B));
            A /= g; B /= g;
        }
        // normalize sign
        if (A < 0 || (A == 0 && B < 0)) {
            A = -A; B = -B;
        }
        // ensure uniqueness
        if (used_dirs.count({A, B})) {
            // retry until new
            i--;
            continue;
        }
        used_dirs.insert({A, B});
        // Generate Cs for this family
        set<int> usedC;
        vector<int> Cs;
        for (int t = 0; t < sizes[i]; t++) {
            int C;
            do {
                C = rnd.next(-10, 10);
            } while (usedC.count(C));
            usedC.insert(C);
            Cs.push_back(C);
        }
        families.push_back({{A, B}, Cs});
    }
    // Gather all lines
    vector<tuple<int,int,int>> lines;
    for (auto &fam : families) {
        int A = fam.first.first;
        int B = fam.first.second;
        for (int C : fam.second) {
            lines.emplace_back(A, B, C);
        }
    }
    // Shuffle order
    shuffle(lines.begin(), lines.end());
    // Output
    println(N);
    for (auto &l : lines) {
        int A, B, C;
        tie(A, B, C) = l;
        println(A, B, C);
    }
    return 0;
}
