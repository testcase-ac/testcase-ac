#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: choose prime or composite length
    vector<int> primes = {2, 3, 5, 7, 11};
    vector<int> composites = {4, 6, 8, 9, 10, 12};
    bool pickPrime = rnd.next(0, 1);
    int N = pickPrime ? rnd.any(primes) : rnd.any(composites);
    // Hyper-parameter: sometimes limit to two distinct letters for diversity
    bool limited = rnd.next(0, 1);
    string plaintext;
    if (limited) {
        char a = char('a' + rnd.next(0, 25));
        char b = char('a' + rnd.next(0, 25));
        while (b == a) b = char('a' + rnd.next(0, 25));
        for (int i = 0; i < N; i++) {
            plaintext.push_back(rnd.next(0, 1) ? a : b);
        }
    } else {
        for (int i = 0; i < N; i++) {
            plaintext.push_back(char('a' + rnd.next(0, 25)));
        }
    }
    // Determine R and C: R*C = N, R <= C, R maximum
    int R = 1, C = N;
    for (int r = 1; r <= N; r++) {
        if (N % r == 0 && r <= N / r) {
            R = r;
        }
    }
    C = N / R;
    // Fill the matrix row-wise
    vector<string> grid(R, string(C, ' '));
    int idx = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            grid[i][j] = plaintext[idx++];
        }
    }
    // Read column-wise to form encrypted message
    string encrypted;
    for (int j = 0; j < C; j++) {
        for (int i = 0; i < R; i++) {
            encrypted.push_back(grid[i][j]);
        }
    }
    // Output the encrypted string as the test case
    println(encrypted);
    return 0;
}
