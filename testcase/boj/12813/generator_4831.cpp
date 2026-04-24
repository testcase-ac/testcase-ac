#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose length N: some small, some medium
    double p = rnd.next();
    int N;
    if (p < 0.2) {
        N = 1;
    } else if (p < 0.5) {
        N = rnd.next(2, 10);
    } else {
        N = rnd.next(11, 100);
    }

    // Generator for a binary string with diverse patterns
    auto gen = [&](int len) {
        string s;
        s.reserve(len);
        int type = rnd.next(0, 5);
        if (type == 0) {
            // all zeros
            s = string(len, '0');
        } else if (type == 1) {
            // all ones
            s = string(len, '1');
        } else if (type == 2) {
            // alternating starting with '0'
            for (int i = 0; i < len; i++)
                s.push_back((i % 2 == 0) ? '0' : '1');
        } else if (type == 3) {
            // alternating starting with '1'
            for (int i = 0; i < len; i++)
                s.push_back((i % 2 == 0) ? '1' : '0');
        } else if (type == 4) {
            // uniform random bits
            for (int i = 0; i < len; i++)
                s.push_back(rnd.next(0, 1) ? '1' : '0');
        } else {
            // random runs of alternating segments
            int pos = 0;
            int bit = rnd.next(0, 1);
            while (pos < len) {
                int run = rnd.next(1, 5);
                for (int k = 0; k < run && pos < len; k++, pos++)
                    s.push_back(bit ? '1' : '0');
                bit ^= 1;
            }
        }
        return s;
    };

    string A = gen(N);
    string B = gen(N);

    printf("%s\n%s\n", A.c_str(), B.c_str());
    return 0;
}
