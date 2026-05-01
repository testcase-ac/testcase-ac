#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string addStrings(const string &a, const string &b) {
    string res;
    int i = (int)a.size() - 1, j = (int)b.size() - 1, carry = 0;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        res.push_back(char('0' + sum % 10));
        carry = sum / 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases between 2 and 6 to ensure Fn=1 case plus others
    int T = rnd.next(2, 6);
    vector<int> ns;
    // Force at least one Fn = 1 case to test duplicate-index (F1=F2=1)
    ns.push_back(1);
    // Generate remaining indices with varied sizes
    for (int i = 1; i < T; i++) {
        double r = rnd.next();
        int n;
        if (r < 0.4) {
            // small indices
            n = rnd.next(1, 10);
        } else if (r < 0.7) {
            // medium
            n = rnd.next(11, 50);
        } else if (r < 0.9) {
            // large
            n = rnd.next(51, 200);
        } else {
            // extra large
            n = rnd.next(201, 1000);
        }
        ns.push_back(n);
    }

    // Compute Fibonacci strings up to max index
    int max_n = *max_element(ns.begin(), ns.end());
    vector<string> F(max_n + 1);
    F[0] = "0";
    if (max_n >= 1) F[1] = "1";
    for (int i = 2; i <= max_n; i++) {
        F[i] = addStrings(F[i-1], F[i-2]);
    }

    // Output
    println(T);
    for (int n : ns) {
        println(F[n]);
    }

    return 0;
}
