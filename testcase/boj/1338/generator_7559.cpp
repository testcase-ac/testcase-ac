#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Generate a non-negative range [A, B] with small size
    int A = rnd.next(0, 10);
    int B = A + rnd.next(0, 20);
    int L = B - A;
    // Decide case type: 0 = no solution, 1 = unique, 2 = multiple
    vector<int> types;
    if (L >= 1) types = {0, 1, 2};
    else types = {0, 1};
    int t = rnd.any(types);
    int x_abs, y;
    if (t == 0) {
        // No solution: step > range length + 1
        // Ensure x_abs >= L+2 so that [A,B] is strictly smaller than one full step
        x_abs = rnd.next(L + 2, L + 11);
        // Pick y outside [A, B]
        while (true) {
            y = rnd.next(0, x_abs - 1);
            if (y < A || y > B) break;
        }
    } else if (t == 1) {
        // Unique solution: step > range length so only one intersection
        x_abs = rnd.next(L + 1, L + 11);
        // Choose a solution point z0 in [A, B], set y = z0 mod x_abs
        int z0 = rnd.next(A, B);
        y = z0 % x_abs;
    } else {
        // Multiple solutions: ensure at least two by choosing a valid z0 and step
        // Step x_abs from 1 to L so that B - x_abs >= A
        x_abs = rnd.next(1, L);
        // Pick a base z0 so that z0 and z0 + x_abs both lie in [A, B]
        int z0 = rnd.next(A, B - x_abs);
        y = z0 % x_abs;
    }
    // Randomize sign of x to include negative divisor cases
    int x = (rnd.next(0, 1) == 0 ? x_abs : -x_abs);
    // Output
    println(A, B);
    println(x, y);
    return 0;
}
