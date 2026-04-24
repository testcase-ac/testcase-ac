#include "testlib.h"
#include <vector>
using namespace std;

vector<int> genScores(int total, random_t& rnd) {
    // Generate 4 scores in [1,5] summing to total
    vector<int> s(4, 1);
    int rem = total - 4;
    for (int i = 0; i < 3; i++) {
        int positions_left = 3 - i;
        // Each remaining score can add up to 4
        int min_add = max(0, rem - 4 * positions_left);
        int max_add = min(4, rem);
        int add = rnd.next(min_add, max_add);
        s[i] += add;
        rem -= add;
    }
    s[3] += rem;
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a unique winner 1..5
    int winner = rnd.next(1, 5);

    // Hyper-parameter to bias winner's score sum
    int t1 = rnd.next(-2, 2);
    // Winner sum in [5..20]
    int rem_w = rnd.wnext(16, t1); // 0..15
    int sum_w = rem_w + 5;         // 5..20

    // Hyper-parameter for losers' distribution
    int t2 = rnd.next(-2, 2);
    // rem_i in [0..sum_w-5] so sum_i in [4..sum_w-1]
    int hi_rem = sum_w - 4;        // >=1

    vector<vector<int>> all(6);
    // Generate winner's scores
    all[winner] = genScores(sum_w, rnd);

    // Generate losers' sums and scores
    for (int i = 1; i <= 5; i++) {
        if (i == winner) continue;
        int rem_i = rnd.wnext(hi_rem, t2); // 0..(sum_w-5)
        int sum_i = rem_i + 4;             // 4..sum_w-1
        all[i] = genScores(sum_i, rnd);
    }

    // Output 5 lines of 4 scores each
    for (int i = 1; i <= 5; i++) {
        println(all[i]);
    }
    return 0;
}
