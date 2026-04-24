#include "testlib.h"
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of test cases
    int tbias = rnd.next(-1, 1);
    int T = rnd.wnext(10, tbias) + 1;  // 1..10
    println(T);

    string opset = "@%#";
    for (int i = 0; i < T; i++) {
        // Hyper-parameter for operator count (1 to 3)
        int op_bias = rnd.next(-2, 2);
        int op_count = rnd.wnext(3, op_bias) + 1;  // 1..3

        // Hyper-parameter for decimal vs integer
        int dec_bias = rnd.next(-1, 1);
        bool is_decimal = (rnd.wnext(2, dec_bias) == 1);

        // Hyper-parameter for integer part distribution
        int ip_bias = rnd.next(-1, 1);
        int max_ip = rnd.wnext(101, ip_bias);  // 0..100 biased
        int int_part = rnd.next(0, max_ip);

        // Build tokens for this test case
        vector<string> tokens;

        // Starting number
        if (is_decimal) {
            int d = rnd.next(0, 9);
            char buf[16];
            sprintf(buf, "%d.%d", int_part, d);
            tokens.emplace_back(buf);
        } else {
            tokens.emplace_back(to_string(int_part));
        }

        // Append operators
        for (int j = 0; j < op_count; j++) {
            char op = rnd.any(opset);
            tokens.emplace_back(string(1, op));
        }

        // Print the test case line
        println(tokens);
    }

    return 0;
}
