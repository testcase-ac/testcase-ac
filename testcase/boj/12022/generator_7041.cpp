#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose size small or medium
    int N;
    if (rnd.next(0, 1) == 0) {
        N = rnd.next(1, 5);
    } else {
        N = rnd.next(6, 15);
    }

    // Hyper-parameters for preference generation schemes
    // 0 = identity [1,2,...,N], 1 = reverse [N,...,1], 2 = fully random per person
    int menScheme = rnd.next(0, 2);
    int womenScheme = rnd.next(0, 2);

    vector<int> base(N);
    iota(base.begin(), base.end(), 1);

    // Generate men's preferences
    vector<vector<int>> men(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        if (menScheme == 0) {
            men[i] = base;
        } else if (menScheme == 1) {
            men[i] = base;
            reverse(men[i].begin(), men[i].end());
        } else {
            men[i] = base;
            shuffle(men[i].begin(), men[i].end());
        }
    }

    // Generate women's preferences
    vector<vector<int>> women(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        if (womenScheme == 0) {
            women[i] = base;
        } else if (womenScheme == 1) {
            women[i] = base;
            reverse(women[i].begin(), women[i].end());
        } else {
            women[i] = base;
            shuffle(women[i].begin(), women[i].end());
        }
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        println(men[i]);
    }
    for (int i = 0; i < N; i++) {
        println(women[i]);
    }

    return 0;
}
