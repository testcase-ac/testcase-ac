#include "testlib.h"
#include <vector>
#include <algorithm>
#include <array>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of players
    int N = rnd.next(2, 10);
    // vals[k][i]: the number player k wrote in game i
    vector<array<int,3>> vals(N);

    // Generate each of the 3 games independently
    for (int game = 0; game < 3; ++game) {
        // Hyper-parameter: how many distinct numbers in this game
        int distinct_count = rnd.next(1, N);

        // Pick distinct_count distinct values in [1,100]
        vector<int> distinct_vals;
        while ((int)distinct_vals.size() < distinct_count) {
            int x = rnd.next(1, 100);
            if (find(distinct_vals.begin(), distinct_vals.end(), x) == distinct_vals.end())
                distinct_vals.push_back(x);
        }

        // Assign at least one player to each distinct value, then distribute the rest
        vector<int> counts(distinct_count, 1);
        for (int extra = 0; extra < N - distinct_count; ++extra) {
            int idx = rnd.next(0, distinct_count - 1);
            counts[idx]++;
        }

        // Build the list of N numbers for this game
        vector<int> round_vals;
        for (int i = 0; i < distinct_count; ++i) {
            for (int c = 0; c < counts[i]; ++c)
                round_vals.push_back(distinct_vals[i]);
        }
        // Shuffle to assign randomly to players
        shuffle(round_vals.begin(), round_vals.end());

        // Record into vals
        for (int player = 0; player < N; ++player)
            vals[player][game] = round_vals[player];
    }

    // Output
    println(N);
    for (int i = 0; i < N; ++i)
        println(vals[i][0], vals[i][1], vals[i][2]);

    return 0;
}
