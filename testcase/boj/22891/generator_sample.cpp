#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct Row {
    int prime;
    long long count;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
        31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
        73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
        127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
        179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
        233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
        283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
        353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
        419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
        467, 479, 487, 491, 499
    };

    int T = rnd.next(1, 8);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 4);
        int m;
        if (mode == 0) {
            m = 1;
        } else if (mode == 1) {
            m = rnd.next(2, 5);
        } else if (mode == 2) {
            m = rnd.next(6, 12);
        } else if (mode == 3) {
            m = rnd.next(1, 6);
        } else {
            m = rnd.next(20, 95);
        }

        vector<int> idx(primes.size());
        iota(idx.begin(), idx.end(), 0);
        shuffle(idx.begin(), idx.end());
        idx.resize(m);
        sort(idx.begin(), idx.end());

        vector<Row> rows;
        long long totalCards = 0;
        for (int i = 0; i < m; ++i) {
            long long count;
            if (mode == 3 && i == m - 1) {
                count = 1000000000000000LL - totalCards;
            } else if (mode == 4) {
                count = rnd.next(1, 3);
            } else {
                count = rnd.next(1, 20);
            }
            rows.push_back({primes[idx[i]], count});
            totalCards += count;
        }

        if (totalCards == 1) {
            rows[0].count = 2;
        }

        println(m);
        for (const Row& row : rows) {
            println(row.prime, row.count);
        }
    }

    return 0;
}
