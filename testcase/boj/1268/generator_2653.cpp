#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of students
    int N = rnd.next(3, 10);
    println(N);

    // Generate class assignments for each of 5 years
    vector<vector<int>> a(N, vector<int>(5));
    for (int y = 0; y < 5; ++y) {
        // Number of distinct classes this year
        int maxK = min(N, 9);
        int K = rnd.next(1, maxK);
        vector<int> labels(9);
        iota(labels.begin(), labels.end(), 1);
        shuffle(labels.begin(), labels.end());
        labels.resize(K);
        // Assign each student to one of these classes
        for (int i = 0; i < N; ++i) {
            a[i][y] = rnd.any(labels);
        }
    }

    // Output assignments
    for (int i = 0; i < N; ++i) {
        println(a[i][0], a[i][1], a[i][2], a[i][3], a[i][4]);
    }

    return 0;
}
