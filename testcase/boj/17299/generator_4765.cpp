#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small size for N
    int N = rnd.next(1, 10);
    // Number of distinct values
    int U = rnd.next(1, N);
    // Maximum value range to pick distinct labels from
    int maxVal = rnd.next(U, max(U, 5));

    // Generate a pool of candidate values [1..maxVal] and pick U distinct values
    vector<int> pool(maxVal);
    for (int i = 0; i < maxVal; i++) pool[i] = i + 1;
    shuffle(pool.begin(), pool.end());
    pool.resize(U); // unique values to use

    // Assign at least one occurrence to each, then distribute the rest
    vector<int> count(U, 1);
    int rem = N - U;
    while (rem > 0) {
        int idx = rnd.next(0, U - 1);
        count[idx]++;
        rem--;
    }

    // Build the sequence
    vector<int> A;
    for (int i = 0; i < U; i++) {
        for (int j = 0; j < count[i]; j++)
            A.push_back(pool[i]);
    }
    // Shuffle to mix positions
    shuffle(A.begin(), A.end());

    // Output
    println(N);
    println(A);

    return 0;
}
