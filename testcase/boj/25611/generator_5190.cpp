#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for diversity
    int N = rnd.next(2, 10);
    int Hmax = rnd.next(5, 20);
    vector<string> shapes = {"random", "increasing", "decreasing", "mountain", "valley", "plateau"};
    vector<string> dists = {"uniform", "wmax", "wmin"};
    string shape = rnd.any(shapes);
    string dist = rnd.any(dists);

    // Generator of a single height based on distribution
    auto genRandom = [&]() {
        int x;
        if (dist == "uniform") {
            x = rnd.next(0, Hmax - 1);
        } else if (dist == "wmax") {
            x = rnd.wnext(Hmax, 2);
        } else { // wmin
            x = rnd.wnext(Hmax, -2);
        }
        return x + 1;
    };

    vector<int> h(N);
    if (shape == "random") {
        for (int i = 0; i < N; i++)
            h[i] = genRandom();
    }
    else if (shape == "increasing") {
        for (int i = 0; i < N; i++) h[i] = genRandom();
        sort(h.begin(), h.end());
    }
    else if (shape == "decreasing") {
        for (int i = 0; i < N; i++) h[i] = genRandom();
        sort(h.begin(), h.end(), greater<int>());
    }
    else if (shape == "mountain") {
        int p = rnd.next(0, N - 1);
        vector<int> left(p + 1), right(N - p - 1);
        for (int i = 0; i < (int)left.size(); i++) left[i] = genRandom();
        for (int i = 0; i < (int)right.size(); i++) right[i] = genRandom();
        sort(left.begin(), left.end());
        sort(right.begin(), right.end(), greater<int>());
        for (int i = 0; i <= p; i++) h[i] = left[i];
        for (int i = p + 1; i < N; i++) h[i] = right[i - p - 1];
    }
    else if (shape == "valley") {
        int p = rnd.next(0, N - 1);
        vector<int> left(p + 1), right(N - p - 1);
        for (int i = 0; i < (int)left.size(); i++) left[i] = genRandom();
        for (int i = 0; i < (int)right.size(); i++) right[i] = genRandom();
        sort(left.begin(), left.end(), greater<int>());
        sort(right.begin(), right.end());
        for (int i = 0; i <= p; i++) h[i] = left[i];
        for (int i = p + 1; i < N; i++) h[i] = right[i - p - 1];
    }
    else if (shape == "plateau") {
        for (int i = 0; i < N; i++) h[i] = genRandom();
        int s = rnd.next(0, N - 2);
        int maxL = min(N - s, 4);
        int l = rnd.next(2, maxL);
        int hp = genRandom();
        for (int i = s; i < s + l; i++) h[i] = hp;
    }

    // Output the test case
    println(N);
    println(h);
    return 0;
}
