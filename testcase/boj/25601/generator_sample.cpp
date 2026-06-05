#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string nameOf(int index) {
    string s;
    do {
        s.push_back(static_cast<char>('a' + index % 26));
        index = index / 26 - 1;
    } while (index >= 0);
    if (s.size() == 1) {
        s.push_back('a');
    }
    return s;
}

bool isAncestor(int a, int b, const vector<int>& parent) {
    for (int v = b; v != -1; v = parent[v]) {
        if (v == a) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(2, 20);

    vector<string> names(n);
    for (int i = 0; i < n; ++i) {
        names[i] = nameOf(i);
    }

    vector<int> parent(n, -1);
    for (int child = 1; child < n; ++child) {
        if (mode == 0) {
            parent[child] = child - 1;
        } else if (mode == 1) {
            parent[child] = 0;
        } else if (mode == 2) {
            parent[child] = (child - 1) / 2;
        } else {
            int bias = rnd.next(-2, 2);
            parent[child] = rnd.wnext(child, bias);
        }
    }

    int a = 0;
    int b = 1;
    int queryMode = rnd.next(0, 3);
    if (queryMode == 0) {
        b = rnd.next(1, n - 1);
        vector<int> ancestors;
        for (int v = parent[b]; v != -1; v = parent[v]) {
            ancestors.push_back(v);
        }
        a = rnd.any(ancestors);
    } else if (queryMode == 1) {
        a = rnd.next(1, n - 1);
        b = parent[a];
    } else {
        for (int attempt = 0; attempt < 100; ++attempt) {
            a = rnd.next(0, n - 1);
            b = rnd.next(0, n - 1);
            if (a != b && !isAncestor(a, b, parent) && !isAncestor(b, a, parent)) {
                break;
            }
        }
        if (a == b) {
            b = (a + 1) % n;
        }
    }

    vector<int> order;
    for (int i = 1; i < n; ++i) {
        order.push_back(i);
    }
    shuffle(order.begin(), order.end());

    println(n);
    for (int child : order) {
        println(names[child], names[parent[child]]);
    }
    println(names[a], names[b]);

    return 0;
}
