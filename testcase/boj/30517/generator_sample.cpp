#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int nextLabel(int& label) {
    return label++;
}

void addPair(vector<int>& a, int label) {
    a.push_back(label);
    a.push_back(label);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> a;
    int label = 1;

    if (mode == 0) {
        int n = rnd.next(1, 40);
        a.assign(n, 0);
    } else if (mode == 1) {
        int pairs = rnd.next(1, 20);
        for (int i = 0; i < pairs; ++i) {
            if (rnd.next(0, 3) == 0) a.push_back(0);
            addPair(a, nextLabel(label));
        }
        if (rnd.next(0, 1)) a.push_back(0);
    } else if (mode == 2) {
        int pairs = rnd.next(1, 25);
        for (int i = 0; i < pairs; ++i) a.push_back(nextLabel(label));
        if (rnd.next(0, 1)) a.push_back(0);
        for (int i = pairs; i >= 1; --i) a.push_back(i);
    } else if (mode == 3) {
        int pairs = rnd.next(2, 25);
        vector<int> labels(pairs);
        iota(labels.begin(), labels.end(), 1);
        label = pairs + 1;
        for (int x : labels) a.push_back(x);
        shuffle(labels.begin(), labels.end());
        for (int x : labels) {
            if (rnd.next(0, 4) == 0) a.push_back(0);
            a.push_back(x);
        }
    } else if (mode == 4) {
        int pairs = rnd.next(2, 20);
        int endpoint = nextLabel(label);
        a.push_back(endpoint);
        for (int i = 1; i < pairs; ++i) {
            int x = nextLabel(label);
            if (rnd.next(0, 2) == 0) {
                addPair(a, x);
            } else {
                a.push_back(x);
                a.push_back(0);
                a.push_back(x);
            }
        }
        a.push_back(endpoint);
    } else {
        int pairs = rnd.next(1, 40);
        int zeros = rnd.next(0, 30);
        for (int i = 0; i < pairs; ++i) addPair(a, nextLabel(label));
        a.insert(a.end(), zeros, 0);
        shuffle(a.begin(), a.end());
    }

    println(static_cast<int>(a.size()));
    println(a);
    return 0;
}
