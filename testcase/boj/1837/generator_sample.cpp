#include "testlib.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <algorithm>
#include <string>
#include <vector>

using boost::multiprecision::cpp_int;
using namespace std;

string toString(cpp_int value) {
    if (value == 0) {
        return "0";
    }
    string result;
    while (value > 0) {
        int digit = static_cast<int>(value % 10);
        result.push_back(static_cast<char>('0' + digit));
        value /= 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> smallPrimes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
        31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
        73, 79, 83, 89, 97, 101, 127, 149, 173, 199,
        251, 307, 401, 499, 631, 809, 997
    };
    const vector<int> mediumPrimes = {
        1009, 1237, 1543, 1999, 2503, 4001, 7919,
        10007, 20011, 40009, 65537, 99991, 250007,
        500009, 999983
    };
    const vector<int> largerPrimes = {
        1000000007, 1000000009
    };

    int mode = rnd.next(0, 6);
    cpp_int p;
    cpp_int q;
    int k;

    if (mode == 0) {
        p = rnd.any(smallPrimes);
        q = rnd.any(smallPrimes);
        int lo = static_cast<int>(min(p, q)) + 1;
        k = rnd.next(2, min(1000000, lo + 50));
    } else if (mode == 1) {
        p = rnd.any(mediumPrimes);
        q = rnd.any(mediumPrimes);
        int lo = static_cast<int>(min(p, q));
        k = rnd.next(2, lo);
    } else if (mode == 2) {
        int r = rnd.any(smallPrimes);
        p = r;
        q = rnd.any(mediumPrimes);
        k = rnd.next(r + 1, min(1000000, r + 1000));
    } else if (mode == 3) {
        int r = rnd.any(smallPrimes);
        p = r;
        q = rnd.any(mediumPrimes);
        k = r;
    } else if (mode == 4) {
        int r = rnd.any(mediumPrimes);
        p = r;
        q = r;
        k = rnd.next(max(2, r - 500), min(1000000, r + 500));
    } else if (mode == 5) {
        p = rnd.any(largerPrimes);
        q = rnd.any(largerPrimes);
        k = rnd.next(2, 1000000);
    } else {
        p = rnd.any(smallPrimes);
        q = rnd.any(mediumPrimes);
        k = rnd.any(vector<int>{2, 3, 10, 12, 999983, 1000000});
    }

    println(toString(p * q), k);
    return 0;
}
