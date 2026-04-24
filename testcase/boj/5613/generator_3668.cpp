#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    vector<int> maxOptions = {5, 10, 20, 50};
    int maxNum = rnd.any(maxOptions);       // upper bound for numbers
    int L = rnd.next(1, 7);                 // number of operations
    int t = rnd.next(-2, 2);                // weight parameter for op choice

    // Build the sequence
    int cur = rnd.next(1, maxNum);
    vector<string> seq;
    seq.push_back(to_string(cur));

    for (int i = 0; i < L; i++) {
        // choose allowed operations
        vector<char> ops = {'+', '-', '*'};
        if (cur >= 0) ops.push_back('/');

        // pick operation with weighted randomness
        int idx = rnd.wnext((int)ops.size(), t);
        char op = ops[idx];

        // pick next operand
        int num = rnd.next(1, maxNum);

        // apply operation to current result
        if (op == '+') {
            cur += num;
        } else if (op == '-') {
            cur -= num;
        } else if (op == '*') {
            cur *= num;
        } else { // '/'
            // divisor guaranteed positive
            cur /= num;
        }

        // append to sequence
        seq.push_back(string(1, op));
        seq.push_back(to_string(num));
    }
    // end with equals
    seq.push_back("=");

    // output each token on its own line
    for (auto &s : seq) {
        println(s);
    }

    return 0;
}
