#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int valueWithResidue(int residue, int k) {
    if (residue == 0) {
        return k * rnd.next(1, 1000000 / k);
    }
    return residue + k * rnd.next(0, (1000000 - residue) / k);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k;
    if (mode == 0) {
        k = rnd.any(vector<int>{1, 2, 3, 512, 100000});
    } else {
        k = rnd.next(1, 100000);
    }

    int n = rnd.next(1, 30);
    vector<int> residues;

    if (k == 1 || n == 1) {
        residues.assign(n, 0);
    } else if (mode == 1) {
        int r = rnd.next(1, k - 1);
        for (int i = 0; i + 1 < n; i += 2) {
            residues.push_back(r);
            residues.push_back(k - r);
        }
        if ((int)residues.size() < n) {
            residues.push_back(0);
        }
    } else if (mode == 2) {
        int groupSize = rnd.next(2, min(n, 6));
        while ((int)residues.size() + groupSize <= n) {
            int sum = 0;
            for (int i = 0; i + 1 < groupSize; ++i) {
                int r = rnd.next(0, k - 1);
                residues.push_back(r);
                sum = (sum + r) % k;
            }
            residues.push_back((k - sum) % k);
        }
        int remaining = n - (int)residues.size();
        int sum = 0;
        for (int i = 0; i + 1 < remaining; ++i) {
            int r = rnd.next(0, k - 1);
            residues.push_back(r);
            sum = (sum + r) % k;
        }
        if (remaining > 0) {
            residues.push_back((k - sum) % k);
        }
    } else if (mode == 3) {
        int target = rnd.next(0, k - 1);
        int current = 0;
        for (int i = 0; i + 1 < n; ++i) {
            int next = (i % 3 == 2 ? target : rnd.next(0, k - 1));
            residues.push_back((next - current + k) % k);
            current = next;
        }
        residues.push_back((k - current) % k);
    } else {
        int sum = 0;
        for (int i = 0; i + 1 < n; ++i) {
            int r = rnd.next(0, k - 1);
            residues.push_back(r);
            sum = (sum + r) % k;
        }
        residues.push_back((k - sum) % k);
    }

    if (mode == 4) {
        shuffle(residues.begin(), residues.end());
    }

    vector<int> weights;
    weights.reserve(n);
    for (int residue : residues) {
        weights.push_back(valueWithResidue(residue, k));
    }

    println(n, k);
    println(weights);

    return 0;
}
