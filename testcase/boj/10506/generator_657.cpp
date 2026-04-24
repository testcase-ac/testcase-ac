#include "testlib.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
bool ispow2(int t) {
    for(int i=0; i<=13; i++) {
        if(t == (1<<i))
            return 1;
    }
    return 0;
}
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = 1;
    println(T);

    int sum = 0, target = 1 << rnd.next(2, 13);
    vector<int> blocks;

    while(sum < target) {
        int remaining = target - sum;

        // Calculate the maximum possible exponent for the remaining sum
        int maxExponent = (int)floor(log2(remaining));
        
        // Generate an exponent between 0 and maxExponent
        int e = rnd.next(0, maxExponent);
        int val = 1 << e;

        sum += val;
        blocks.push_back(val);

        remaining = target - sum;
        if(ispow2(remaining)) {
            break;
        }
    }
    if(sum < target) {
        blocks.push_back(target-sum);
    }

    // Adjust 'n' in case we couldn't generate enough blocks
    int n = blocks.size();
    // Output the adjusted 'n' if it has changed
    println(n);

    shuffle(blocks.begin(), blocks.end());

    // Output the block lengths
    for (int i = 0; i < n; ++i) {
        cout << blocks[i];
        if (i != n - 1) cout << " ";
    }
    cout << '\n';

    return 0;
}
