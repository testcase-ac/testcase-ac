#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    int k = rnd.next(0, n);
    vector<long long> breeds;

    auto nextBreed = [&]() {
        long long value;
        do {
            value = rnd.next(0LL, 1000000000LL);
        } while (find(breeds.begin(), breeds.end(), value) != breeds.end());
        breeds.push_back(value);
        return value;
    };

    vector<long long> cows;
    if (mode == 0) {
        long long breed = nextBreed();
        cows.assign(n, breed);
        k = rnd.next(0, n);
    } else if (mode == 1) {
        n = rnd.next(1, 18);
        k = rnd.next(0, n);
        for (int i = 0; i < n; ++i) cows.push_back(nextBreed());
    } else if (mode == 2) {
        long long target = nextBreed();
        int noiseKinds = rnd.next(1, min(6, n));
        vector<long long> noise;
        for (int i = 0; i < noiseKinds; ++i) noise.push_back(nextBreed());

        k = rnd.next(0, noiseKinds);
        for (int i = 0; i < n; ++i) {
            if (i % rnd.next(2, 4) == 0) {
                cows.push_back(rnd.any(noise));
            } else {
                cows.push_back(target);
            }
        }
    } else if (mode == 3) {
        int kinds = rnd.next(2, min(7, n + 1));
        for (int i = 0; i < kinds; ++i) nextBreed();
        k = rnd.next(0, min(n, kinds - 1));

        while ((int)cows.size() < n) {
            long long breed = rnd.any(breeds);
            int block = rnd.next(1, 5);
            while (block-- > 0 && (int)cows.size() < n) cows.push_back(breed);
        }
    } else if (mode == 4) {
        long long low = 0;
        long long high = 1000000000LL;
        long long mid = nextBreed();
        breeds.push_back(low);
        breeds.push_back(high);
        k = rnd.next(0, min(n, 2));
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(0, 2);
            cows.push_back(pick == 0 ? low : pick == 1 ? mid : high);
        }
    } else {
        int kinds = rnd.next(1, min(8, n));
        for (int i = 0; i < kinds; ++i) nextBreed();
        k = rnd.next(0, min(n, kinds));

        for (int i = 0; i < n; ++i) cows.push_back(rnd.any(breeds));
        shuffle(cows.begin(), cows.end());
    }

    println(n, k);
    for (long long breed : cows) println(breed);
    return 0;
}
