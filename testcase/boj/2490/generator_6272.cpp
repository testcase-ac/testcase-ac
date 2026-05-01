#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // We need exactly 3 lines of input, each with 4 bits (0 or 1).
    for (int i = 0; i < 3; i++) {
        // Hyper-parameter t controls bias: positive t => more zeros, negative t => fewer zeros
        int t = rnd.next(-2, 2);
        // Generate number of zeros in [0..4] with weighted distribution
        int zeros = rnd.wnext(5, t);
        // Build the 4 bits: zeros count of 0s, rest 1s
        vector<int> bits(4, 1);
        for (int j = 0; j < zeros && j < 4; j++) bits[j] = 0;
        shuffle(bits.begin(), bits.end());
        // Output one line of 4 bits
        println(bits);
    }
    return 0;
}
