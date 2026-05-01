#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(1, 12);
    bool all_zero = rnd.next(0, 9) == 0;
    vector<string> a;
    vector<string> special = {"12", "121", "9", "98", "91", "34", "343", "30", "303"};
    bool has_non_zero = false;

    if (all_zero) {
        for (int i = 0; i < N; i++)
            a.push_back("0");
    } else {
        for (int i = 0; i < N; i++) {
            double p = rnd.next();
            string s;
            if (p < 0.1) {
                s = "0";
            } else if (p < 0.4) {
                s = rnd.any(special);
            } else {
                int len = rnd.next(1, 9);
                s.resize(len);
                s[0] = char('1' + rnd.next(0, 8));
                for (int j = 1; j < len; j++)
                    s[j] = char('0' + rnd.next(0, 9));
            }
            if (s != "0") has_non_zero = true;
            a.push_back(s);
        }
        if (!has_non_zero) {
            a[0] = rnd.any(special);
        }
    }

    shuffle(a.begin(), a.end());
    println(N);
    println(a);
    return 0;
}
