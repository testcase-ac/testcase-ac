#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Prepare candidate values: 10, 20, ..., 990
    vector<int> cand;
    for (int v = 10; v < 1000; v += 10)
        cand.push_back(v);

    // Choose scenario: 0 = all distinct, 1 = one unique mode, 2 = multiple modes tie
    int scenario = rnd.next(0, 2);
    vector<int> a;

    if (scenario == 0) {
        // All distinct
        vector<int> arr = cand;
        shuffle(arr.begin(), arr.end());
        for (int i = 0; i < 10; i++)
            a.push_back(arr[i]);
    }
    else if (scenario == 1) {
        // One clear mode
        vector<int> arr = cand;
        shuffle(arr.begin(), arr.end());
        int x = arr[0];
        int f = rnd.next(2, 9); // frequency of the mode, leave at least one other
        for (int i = 0; i < f; i++)
            a.push_back(x);
        // Fill the rest with distinct values != x
        for (int i = 1; (int)a.size() < 10; i++)
            a.push_back(arr[i]);
    }
    else {
        // Multiple modes tie
        vector<int> arr = cand;
        shuffle(arr.begin(), arr.end());
        int k = rnd.next(2, 4);       // number of modes
        int maxf = 10 / k;            // floor
        int f = rnd.next(2, maxf);    // frequency for each mode
        // Take k distinct mode values
        for (int i = 0; i < k; i++)
            for (int t = 0; t < f; t++)
                a.push_back(arr[i]);
        // Fill remainder with distinct non-mode values
        int used = k * f;
        for (int i = k; used < 10; i++, used++)
            a.push_back(arr[i]);
    }

    // Final shuffle to mix positions
    shuffle(a.begin(), a.end());
    // Output exactly 10 lines
    for (int x : a)
        println(x);

    return 0;
}
