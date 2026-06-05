#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 25);
    vector<int> elsie;
    int mode = rnd.next(6);

    if (mode == 0) {
        for (int i = 1; i <= n; ++i) elsie.push_back(i);
    } else if (mode == 1) {
        for (int i = n + 1; i <= 2 * n; ++i) elsie.push_back(i);
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) elsie.push_back(2 * i - 1);
    } else if (mode == 3) {
        for (int i = 1; i <= n; ++i) elsie.push_back(2 * i);
    } else if (mode == 4) {
        int lo = 1, hi = 2 * n;
        while ((int)elsie.size() < n) {
            if ((int)elsie.size() % 2 == 0) {
                elsie.push_back(lo++);
            } else {
                elsie.push_back(hi--);
            }
        }
    } else {
        vector<int> deck;
        for (int i = 1; i <= 2 * n; ++i) deck.push_back(i);
        shuffle(deck.begin(), deck.end());
        elsie.assign(deck.begin(), deck.begin() + n);
    }

    int order = rnd.next(5);
    if (order == 0) {
        sort(elsie.begin(), elsie.end());
    } else if (order == 1) {
        sort(elsie.rbegin(), elsie.rend());
    } else if (order == 2) {
        shuffle(elsie.begin(), elsie.end());
    } else if (order == 3) {
        vector<int> ordered;
        sort(elsie.begin(), elsie.end());
        int left = 0, right = (int)elsie.size() - 1;
        while (left <= right) {
            ordered.push_back(elsie[left++]);
            if (left <= right) ordered.push_back(elsie[right--]);
        }
        elsie = ordered;
    } else {
        vector<int> ordered;
        sort(elsie.begin(), elsie.end());
        int left = 0, right = (int)elsie.size() - 1;
        while (left <= right) {
            ordered.push_back(elsie[right--]);
            if (left <= right) ordered.push_back(elsie[left++]);
        }
        elsie = ordered;
    }

    println(n);
    for (int card : elsie) println(card);

    return 0;
}
