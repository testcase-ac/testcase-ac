#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Coffee {
    long long cups;
    long long deadline;
    int satisfaction;
};

long long randomNear(long long limit) {
    if (limit <= 20) {
        return rnd.next(1LL, limit);
    }

    int mode = rnd.next(0, 3);
    if (mode == 0) {
        return rnd.next(1LL, min(limit, 20LL));
    }
    if (mode == 1) {
        long long span = min(limit, 1000LL);
        return limit - rnd.next(0LL, span - 1);
    }
    return rnd.next(1LL, limit);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 8);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 5);
        int N = rnd.next(1, 12);
        long long K;

        if (mode == 0) {
            K = rnd.next(1LL, 8LL);
        } else if (mode == 1) {
            K = rnd.next(9LL, 40LL);
        } else if (mode == 2) {
            K = rnd.next(100LL, 10000LL);
        } else if (mode == 3) {
            K = rnd.next(1000000000000LL, 2000000000000LL);
        } else {
            K = rnd.next(1LL, 2000000000000LL);
        }

        println(N, K);

        vector<Coffee> coffee;
        coffee.reserve(N);

        long long sharedDeadline = randomNear(K);
        for (int i = 0; i < N; ++i) {
            Coffee item;

            if (mode == 0) {
                item.deadline = rnd.next(1LL, K);
                item.cups = rnd.next(1LL, K);
            } else if (mode == 1) {
                item.deadline = sharedDeadline;
                item.cups = rnd.next(1LL, K);
            } else if (mode == 2) {
                item.deadline = min(K, max(1LL, 1LL + i * max(1LL, K / max(1, N))));
                if (rnd.next(0, 1)) {
                    item.deadline = randomNear(K);
                }
                item.cups = rnd.next(1LL, min(K, 30LL));
            } else if (mode == 3) {
                item.deadline = randomNear(K);
                item.cups = rnd.next(max(1LL, K - 1000), K);
            } else {
                item.deadline = randomNear(K);
                item.cups = randomNear(K);
            }

            int scoreMode = rnd.next(0, 3);
            if (scoreMode == 0) {
                item.satisfaction = rnd.next(1, 10);
            } else if (scoreMode == 1) {
                item.satisfaction = rnd.next(990, 1000);
            } else {
                item.satisfaction = rnd.next(1, 1000);
            }

            coffee.push_back(item);
        }

        if (mode == 2) {
            sort(coffee.begin(), coffee.end(), [](const Coffee& a, const Coffee& b) {
                return a.deadline < b.deadline;
            });
        } else {
            shuffle(coffee.begin(), coffee.end());
        }

        for (const Coffee& item : coffee) {
            println(item.cups, item.deadline, item.satisfaction);
        }
    }

    return 0;
}
