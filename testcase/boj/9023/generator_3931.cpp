#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);

    vector<string> types = {"random", "identical", "reverse", "shift", "repeat", "cluster"};

    for (int tc = 0; tc < T; tc++) {
        // Costs
        int C = rnd.next(1, 10);
        int D = rnd.next(1, 10);
        int d = rnd.next(1, 10);
        println(C, D, d);

        // Choose pattern type
        string type = rnd.any(types);

        vector<int> seqX, seqY;
        int lenX, lenY;

        if (type == "random") {
            lenX = rnd.next(3, 10);
            lenY = rnd.next(3, 10);
            for (int i = 0; i < lenX; i++)
                seqX.push_back(rnd.next(1, 7));
            for (int i = 0; i < lenY; i++)
                seqY.push_back(rnd.next(1, 7));
        }
        else if (type == "identical") {
            lenX = rnd.next(3, 10);
            for (int i = 0; i < lenX; i++)
                seqX.push_back(rnd.next(1, 7));
            seqY = seqX;
        }
        else if (type == "reverse") {
            lenX = rnd.next(3, 10);
            for (int i = 0; i < lenX; i++)
                seqX.push_back(rnd.next(1, 7));
            seqY = seqX;
            reverse(seqY.begin(), seqY.end());
        }
        else if (type == "shift") {
            lenX = rnd.next(3, 10);
            for (int i = 0; i < lenX; i++)
                seqX.push_back(rnd.next(1, 7));
            int k = rnd.next(1, lenX - 1);
            for (int i = 0; i < lenX; i++)
                seqY.push_back(seqX[(i + k) % lenX]);
        }
        else if (type == "repeat") {
            lenX = rnd.next(3, 10);
            for (int i = 0; i < lenX; i++)
                seqX.push_back(rnd.next(1, 7));
            seqY = seqX;
            int pos = rnd.next(0, lenX - 1);
            seqY.insert(seqY.begin() + pos, seqY[pos]);
        }
        else if (type == "cluster") {
            // X has clusters; Y random
            lenX = rnd.next(3, 10);
            int U = rnd.next(2, min(lenX, 5));
            vector<int> pool(7);
            iota(pool.begin(), pool.end(), 1);
            shuffle(pool.begin(), pool.end());
            pool.resize(U);
            for (int i = 0; i < lenX; i++) {
                if (i > 0 && rnd.next() < 0.6)
                    seqX.push_back(seqX.back());
                else
                    seqX.push_back(rnd.any(pool));
            }
            lenY = rnd.next(3, 10);
            for (int i = 0; i < lenY; i++)
                seqY.push_back(rnd.next(1, 7));
        }

        // Print sequences with terminating zero
        {
            vector<int> tmp = seqX;
            tmp.push_back(0);
            println(tmp);
        }
        {
            vector<int> tmp = seqY;
            tmp.push_back(0);
            println(tmp);
        }
    }

    return 0;
}
