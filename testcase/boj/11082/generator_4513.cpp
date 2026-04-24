#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose representation type
    // 0 = pure integer, 1 = terminating decimal, 2 = repeating decimal
    int typ = rnd.next(0, 2);

    // Generate integer part
    string ip;
    // 20% chance to be zero
    if (rnd.next(0, 4) == 0) {
        ip = "0";
    } else {
        int L = rnd.next(1, 3);
        ip.reserve(L);
        // first digit non-zero
        ip.push_back(char('1' + rnd.next(0, 8)));
        for (int i = 1; i < L; i++) {
            ip.push_back(char('0' + rnd.next(0, 9)));
        }
    }

    if (typ == 0) {
        // Pure integer
        printf("%s\n", ip.c_str());
    } else if (typ == 1) {
        // Terminating decimal
        // max decimals so total length <=10
        int maxK = min(5, 9 - (int)ip.size());
        maxK = max(1, maxK);
        int k = rnd.next(1, maxK);
        string s;
        s.reserve(k);
        for (int i = 0; i < k; i++) {
            s.push_back(char('0' + rnd.next(0, 9)));
        }
        printf("%s.%s\n", ip.c_str(), s.c_str());
    } else {
        // Repeating decimal
        // total length = ip + 1(dot) + k(nonrep) + 2(parens) + r(rep) <= 10
        int remMax = 10 - (int)ip.size() - 3; // k + r <= remMax, r>=1
        remMax = max(remMax, 1);
        int maxK = min(3, remMax - 1);
        int k = (maxK > 0 ? rnd.next(0, maxK) : 0);
        int rMax = remMax - k;
        int r = rnd.next(1, min(3, rMax));
        string nonrep, rep;
        nonrep.reserve(k);
        rep.reserve(r);
        for (int i = 0; i < k; i++) nonrep.push_back(char('0' + rnd.next(0, 9)));
        for (int i = 0; i < r; i++) rep.push_back(char('0' + rnd.next(0, 9)));
        // Assemble
        string out = ip + "." + nonrep + "(" + rep + ")";
        printf("%s\n", out.c_str());
    }

    return 0;
}
