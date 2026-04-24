#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small n for hand-checkable cases
    int n = rnd.next(2, 10);

    // Hyper-parameter for goods distribution
    int mode_g = rnd.next(0, 2);
    vector<int> base_g;
    for (int i = 1; i <= 100; i++) base_g.push_back(i);
    shuffle(base_g.begin(), base_g.end());
    base_g.resize(n);

    vector<int> goods;
    if (mode_g == 1) {
        // almost sorted
        sort(base_g.begin(), base_g.end());
        goods = base_g;
        int K = rnd.next(1, n - 1);
        for (int t = 0; t < K; t++) {
            int i = rnd.next(0, n - 1), j = rnd.next(0, n - 1);
            swap(goods[i], goods[j]);
        }
    } else if (mode_g == 2) {
        // clustered around a few centers
        int maxk = min(n, 4);
        int k = rnd.next(2, maxk);
        set<int> centers_set;
        while ((int)centers_set.size() < k)
            centers_set.insert(rnd.next(1, 100));
        vector<int> centers(centers_set.begin(), centers_set.end());
        set<int> s;
        int idx = 0;
        while ((int)s.size() < n) {
            int c = centers[idx % k];
            int off = rnd.next(-10, 10);
            int v = c + off;
            if (v < 1) v = 1;
            if (v > 100) v = 100;
            s.insert(v);
            idx++;
        }
        goods.assign(s.begin(), s.end());
        shuffle(goods.begin(), goods.end());
    } else {
        // fully random
        goods = base_g;
        shuffle(goods.begin(), goods.end());
    }

    // Hyper-parameter for tags distribution
    int mode_t = rnd.next(0, 2);
    vector<int> base_t;
    for (int i = 1; i <= 100; i++) base_t.push_back(i);
    shuffle(base_t.begin(), base_t.end());
    base_t.resize(n);

    vector<int> tags;
    if (mode_t == 1) {
        // almost sorted
        sort(base_t.begin(), base_t.end());
        tags = base_t;
        int K = rnd.next(1, n - 1);
        for (int t = 0; t < K; t++) {
            int i = rnd.next(0, n - 1), j = rnd.next(0, n - 1);
            swap(tags[i], tags[j]);
        }
    } else if (mode_t == 2) {
        // clustered around a few centers
        int maxk = min(n, 4);
        int k = rnd.next(2, maxk);
        set<int> centers_set;
        while ((int)centers_set.size() < k)
            centers_set.insert(rnd.next(1, 100));
        vector<int> centers(centers_set.begin(), centers_set.end());
        set<int> s;
        int idx = 0;
        while ((int)s.size() < n) {
            int c = centers[idx % k];
            int off = rnd.next(-10, 10);
            int v = c + off;
            if (v < 1) v = 1;
            if (v > 100) v = 100;
            s.insert(v);
            idx++;
        }
        tags.assign(s.begin(), s.end());
        shuffle(tags.begin(), tags.end());
    } else {
        // fully random
        tags = base_t;
        shuffle(tags.begin(), tags.end());
    }

    // Output the test case
    println(n);
    println(goods);
    println(tags);

    return 0;
}
