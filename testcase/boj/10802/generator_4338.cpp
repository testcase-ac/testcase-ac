#include "testlib.h"
#include <string>
using namespace std;

string randomBigInt(int len) {
    // Generate a random positive integer of given length, no leading zeros
    string s;
    s.reserve(len);
    s.push_back(char('0' + rnd.next(1, 9)));
    for (int i = 1; i < len; i++) {
        s.push_back(char('0' + rnd.next(0, 9)));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    double p = rnd.next();
    string A, B;

    if (p < 0.1) {
        // Trivial single-digit range
        int a = rnd.next(1, 9);
        int b = rnd.next(a, 9);
        A = to_string(a);
        B = to_string(b);
    }
    else if (p < 0.2) {
        // Start at 1, end at a random big number
        A = "1";
        int lenB = rnd.next(1, 20);
        B = randomBigInt(lenB);
    }
    else if (p < 0.35) {
        // A == B
        int len = rnd.next(1, 20);
        A = randomBigInt(len);
        B = A;
    }
    else if (p < 0.55) {
        // Small difference branch: B = A + small delta (<=10)
        int len = rnd.next(1, 18);
        // Generate A as unsigned long long
        unsigned long long aLL = 0;
        // First digit
        aLL = rnd.next(1ULL, 9ULL);
        // Rest digits
        for (int i = 1; i < len; i++) {
            aLL = aLL * 10 + rnd.next(0ULL, 9ULL);
        }
        unsigned long long diff = rnd.next(0ULL, 10ULL);
        unsigned long long bLL = aLL + diff;
        A = to_string(aLL);
        B = to_string(bLL);
    }
    else {
        // General random big integers
        int lenA = rnd.next(1, 20);
        int lenB = rnd.next(lenA, 20);
        A = randomBigInt(lenA);
        B = randomBigInt(lenB);
    }

    // Ensure A <= B lexicographically as big integers
    if (A.size() > B.size() || (A.size() == B.size() && A > B)) {
        swap(A, B);
    }

    // Output the single test case
    println(A, B);

    return 0;
}
