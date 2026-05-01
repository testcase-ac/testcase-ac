#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

struct Test {
    int n;
    vector<int> a;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Test> tests;

    // Manual tricky case from statement: optimal needs non-trivial permutation
    {
        Test t;
        t.n = 5;
        t.a = {1, 2, 3, 4};
        tests.push_back(t);
    }

    // Another manual tricky case
    if (rnd.next(0, 1) == 1) {
        Test t;
        t.n = 9;
        t.a = {2, 3, 4, 9};
        tests.push_back(t);
    }

    // k = 0 (empty array)
    {
        Test t;
        t.n = rnd.next(0, 50);
        t.a.clear();
        tests.push_back(t);
    }

    // n = 0 (result depends on largest element)
    {
        Test t;
        t.n = 0;
        int k = rnd.next(1, 5);
        t.a.resize(k);
        for (int i = 0; i < k; i++)
            t.a[i] = rnd.next(0, 20);
        tests.push_back(t);
    }

    // All zeros in array
    {
        Test t;
        t.n = rnd.next(0, 50);
        int k = rnd.next(1, 5);
        t.a.assign(k, 0);
        tests.push_back(t);
    }

    // Helper: S < n, so we never reach n <= 0
    auto makeSumLess = [&]() -> Test {
        Test t;
        int k = rnd.next(1, 6);
        t.a.resize(k);
        for (int i = 0; i < k; i++)
            t.a[i] = rnd.next(0, 10);
        long long S = accumulate(t.a.begin(), t.a.end(), 0LL);
        if (S == 0)
            t.n = rnd.next(1, 30);
        else
            t.n = (int)(S + rnd.next(1, 10)); // ensures n > S
        return t;
    };

    // Helper: S >= n and S - maxA < n so using all elements is optimal
    auto makeFullOptimal = [&]() -> Test {
        while (true) {
            Test t;
            int k = rnd.next(2, 6);
            t.a.resize(k);
            for (int i = 0; i < k; i++)
                t.a[i] = rnd.next(1, 15); // positive
            int maxA = 0;
            for (int x : t.a) maxA = max(maxA, x);
            int S = accumulate(t.a.begin(), t.a.end(), 0);
            int lowN = max(1, S - maxA + 1);
            int highN = S;
            if (lowN <= highN) {
                t.n = rnd.next(lowN, highN); // ensures S - maxA < n <= S
                return t;
            }
        }
    };

    tests.push_back(makeSumLess());
    tests.push_back(makeFullOptimal());

    // Ensure T within limits
    int T = (int)tests.size();
    if (T > 10) T = 10;

    println(T);
    for (int i = 0; i < T; i++) {
        const Test &t = tests[i];
        int n = t.n;
        int k = (int)t.a.size();
        println(n, k);
        if (k == 0) {
            println("");
        } else {
            println(t.a);
        }
    }

    return 0;
}
