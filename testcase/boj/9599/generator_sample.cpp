#include "testlib.h"
#include <tuple>
#include <vector>
using namespace std;

int randomSubsetSum(int n, int k) {
    vector<int> values;
    for (int i = 1; i <= n; ++i) values.push_back(i);
    shuffle(values.begin(), values.end());

    int sum = 0;
    for (int i = 0; i < k; ++i) sum += values[i];
    return sum;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<tuple<int, int, int>> datasets;
    int datasetCount = rnd.next(12, 30);

    datasets.emplace_back(1, 1, 1);
    datasets.emplace_back(20, 10, 155);
    datasets.emplace_back(20, 10, rnd.next(1, 155));
    datasets.emplace_back(rnd.next(1, 9), 10, rnd.next(1, 155));

    while ((int)datasets.size() < datasetCount) {
        int mode = rnd.next(0, 5);
        int n = rnd.next(1, 20);
        int k = rnd.next(1, 10);
        int s;

        if (mode == 0 && k <= n) {
            s = randomSubsetSum(n, k);
        } else if (mode == 1) {
            int minSum = k * (k + 1) / 2;
            s = rnd.next(1, min(155, max(1, minSum - 1)));
        } else if (mode == 2 && k <= n) {
            int maxSum = k * (2 * n - k + 1) / 2;
            s = rnd.next(min(155, maxSum + 1), 155);
        } else if (mode == 3) {
            s = rnd.any(vector<int>{1, 2, 3, 153, 154, 155});
        } else {
            s = rnd.next(1, 155);
        }

        datasets.emplace_back(n, k, s);
    }

    for (auto [n, k, s] : datasets) {
        println(n, k, s);
    }
    println(0, 0, 0);

    return 0;
}
