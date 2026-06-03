#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> ancestorsFromNode(int x) {
    vector<int> path;
    while (x >= 2) {
        path.push_back(x);
        x /= 2;
    }
    reverse(path.begin(), path.end());
    return path;
}

static void addRandomRequests(vector<int>& requests, int n, int targetSize) {
    while ((int)requests.size() < targetSize) {
        requests.push_back(rnd.next(2, n));
    }
}

static int boundedDescendant(int x, int n) {
    while (x * 2 <= n && rnd.next(0, 1)) {
        x = x * 2 + rnd.next(0, min(1, n - x * 2));
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> requests;

    if (mode == 0) {
        n = rnd.next(6, 30);
        int leaf = rnd.next(max(2, n / 2), n);
        requests = ancestorsFromNode(leaf);
        addRandomRequests(requests, n, rnd.next(8, 18));
        shuffle(requests.begin() + 1, requests.end());
    } else if (mode == 1) {
        int height = rnd.next(3, 9);
        n = (1 << height) - 1;
        int base = rnd.next(2, (1 << (height - 1)) - 1);
        int left = boundedDescendant(base * 2, n);
        int right = boundedDescendant(base * 2 + 1, n);
        requests.push_back(left);
        requests.push_back(right);
        requests.push_back(base);
        addRandomRequests(requests, n, rnd.next(10, 24));
    } else if (mode == 2) {
        n = rnd.next(2, 40);
        int repeated = rnd.next(2, n);
        int q = rnd.next(6, 25);
        for (int i = 0; i < q; ++i) {
            if (rnd.next(0, 2) == 0) {
                requests.push_back(repeated);
            } else {
                requests.push_back(rnd.next(2, n));
            }
        }
    } else if (mode == 3) {
        int height = rnd.next(2, 8);
        n = rnd.next(1 << height, min((1 << (height + 1)) - 1, (1 << 20) - 1));
        int parent = rnd.next(1, n / 2);
        requests.push_back(parent * 2);
        if (parent * 2 + 1 <= n) {
            requests.push_back(parent * 2 + 1);
        }
        requests.push_back(parent == 1 ? 2 : parent);
        addRandomRequests(requests, n, rnd.next(8, 22));
    } else if (mode == 4) {
        n = rnd.next((1 << 19), (1 << 20) - 1);
        int q = rnd.next(12, 45);
        for (int i = 0; i < q; ++i) {
            if (rnd.next(0, 3) == 0) {
                requests.push_back(rnd.next(2, 200));
            } else {
                requests.push_back(rnd.next(n - 5000, n));
            }
        }
    } else {
        n = rnd.next(2, 120);
        int q = rnd.next(15, 60);
        for (int i = 0; i < q; ++i) {
            int x = rnd.next(2, n);
            if (!requests.empty() && rnd.next(0, 4) == 0) {
                x = boundedDescendant(rnd.any(requests), n);
            }
            requests.push_back(x);
        }
    }

    println(n, (int)requests.size());
    for (int x : requests) {
        println(x);
    }

    return 0;
}
