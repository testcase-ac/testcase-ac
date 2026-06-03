#include "testlib.h"

#include <vector>

using namespace std;

vector<int> primesUpTo(int limit) {
    vector<bool> composite(limit + 1);
    vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (composite[i]) continue;
        primes.push_back(i);
        if (1LL * i * i <= limit) {
            for (int j = i * i; j <= limit; j += i) composite[j] = true;
        }
    }
    return primes;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int sizeMode = rnd.next(100);
    if (sizeMode < 65) {
        n = rnd.next(2, 4);
    } else if (sizeMode < 90) {
        n = rnd.next(5, 7);
    } else {
        n = rnd.next(8, 10);
    }

    int size = n * n;
    int cells = size * size;

    vector<int> primes = primesUpTo(1000000);
    shuffle(primes.begin(), primes.end());

    vector<vector<int>> board(size, vector<int>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            board[i][j] = primes[i * size + j];
        }
    }

    int zeroMode = rnd.next(4);
    int targetZeros;
    if (zeroMode == 0) {
        targetZeros = 1;
    } else if (zeroMode == 1) {
        targetZeros = rnd.next(2, cells / 4);
    } else if (zeroMode == 2) {
        targetZeros = rnd.next(cells / 4, cells / 2);
    } else {
        targetZeros = rnd.next(cells / 2, cells - 1);
    }

    vector<int> order(cells);
    for (int i = 0; i < cells; ++i) order[i] = i;
    shuffle(order.begin(), order.end());
    for (int k = 0; k < targetZeros; ++k) {
        int pos = order[k];
        board[pos / size][pos % size] = 0;
    }

    println(n);
    for (int i = 0; i < size; ++i) {
        println(board[i]);
    }

    return 0;
}
