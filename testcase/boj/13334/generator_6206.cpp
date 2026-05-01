#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter for n
    vector<int> n_choices = {1, 2, 3, 5, 8, 10, 15};
    int n = rnd.any(n_choices);

    // Coordinate bound
    vector<int> B_choices = {10, 20, 50, 100};
    int B = rnd.any(B_choices);

    // Rail length d
    int d = rnd.next(1, 2 * B);

    // Cluster setup
    int maxClusters = min(n, 3);
    int C = rnd.next(0, maxClusters);
    vector<int> centers;
    for (int i = 0; i < C; i++) {
        centers.push_back(rnd.next(-B, B));
    }
    int r = max(1, B / 5);

    // Generate pairs
    vector<pair<int,int>> people;
    people.reserve(n);
    for (int i = 0; i < n; i++) {
        int h, o;
        if (C > 0 && rnd.next() < 0.6) {
            // clustered
            int c = rnd.any(centers);
            h = c + rnd.next(-r, r);
            o = c + rnd.next(-r, r);
        } else {
            // random global
            h = rnd.next(-B, B);
            o = rnd.next(-B, B);
        }
        if (h == o) {
            // ensure distinct
            if (h + 1 <= B) o = h + 1;
            else o = h - 1;
        }
        people.emplace_back(h, o);
    }
    // Shuffle order
    shuffle(people.begin(), people.end());

    // Output
    println(n);
    for (auto &p : people) {
        println(p.first, p.second);
    }
    println(d);

    return 0;
}
