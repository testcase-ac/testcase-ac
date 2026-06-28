#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Visitor {
    int t;
    vector<int> offices;
};

static vector<int> randomOffices(int m, int k) {
    vector<int> offices;
    offices.reserve(k);
    for (int i = 0; i < k; ++i) {
        offices.push_back(rnd.next(1, m));
    }
    return offices;
}

static vector<int> repeatedOffice(int office, int k) {
    return vector<int>(k, office);
}

static vector<int> alternatingOffices(int first, int second, int k) {
    vector<int> offices;
    offices.reserve(k);
    for (int i = 0; i < k; ++i) {
        offices.push_back(i % 2 == 0 ? first : second);
    }
    return offices;
}

static void printCase(const vector<Visitor>& visitors, int m) {
    println((int)visitors.size(), m);
    for (const Visitor& visitor : visitors) {
        printf("%d %d", visitor.t, (int)visitor.offices.size());
        for (int office : visitor.offices) {
            printf(" %d", office);
        }
        printf("\n");
    }
}

static vector<Visitor> simultaneousQueueCase() {
    int n = rnd.next(3, 8);
    int m = rnd.next(2, 5);
    int shared = rnd.next(1, m);
    int start = rnd.next(0, 8);

    vector<Visitor> visitors;
    for (int i = 0; i < n; ++i) {
        int k = rnd.next(1, 5);
        vector<int> offices;
        offices.push_back(shared);
        while ((int)offices.size() < k) {
            offices.push_back(rnd.next(1, m));
        }
        visitors.push_back({start, offices});
    }
    return visitors;
}

static vector<Visitor> repeatedVisitCase() {
    int n = rnd.next(1, 5);
    int m = rnd.next(1, 4);
    int office = rnd.next(1, m);

    vector<Visitor> visitors;
    for (int i = 0; i < n; ++i) {
        int t = rnd.next(0, 6);
        int k = rnd.next(3, 8);
        visitors.push_back({t, repeatedOffice(office, k)});
    }
    return visitors;
}

static vector<Visitor> crossingRoutesCase() {
    int n = rnd.next(4, 8);
    int m = rnd.next(2, 6);

    vector<Visitor> visitors;
    for (int i = 0; i < n; ++i) {
        int k = rnd.next(2, 6);
        int first = i % m + 1;
        int second = (m - (i % m) - 1 + m) % m + 1;
        visitors.push_back({rnd.next(0, 5), alternatingOffices(first, second, k)});
    }
    return visitors;
}

static vector<Visitor> staggeredCase() {
    int n = rnd.next(3, 9);
    int m = rnd.next(2, 8);

    vector<Visitor> visitors;
    for (int i = 0; i < n; ++i) {
        int t = i * rnd.next(1, 3) + rnd.next(0, 2);
        int k = rnd.next(1, 5);
        visitors.push_back({t, randomOffices(m, k)});
    }
    return visitors;
}

static vector<Visitor> boundaryTimeCase() {
    int n = rnd.next(2, 5);
    int m = rnd.next(1, 5);

    vector<Visitor> visitors;
    for (int i = 0; i < n; ++i) {
        int t = (i == 0 ? 1000000 : rnd.next(999995, 1000000));
        int k = rnd.next(1, 3);
        visitors.push_back({t, randomOffices(m, k)});
    }
    return visitors;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int c = rnd.next(1, 5);
    println(c);

    for (int tc = 0; tc < c; ++tc) {
        int mode = rnd.next(0, 4);
        vector<Visitor> visitors;

        if (mode == 0) {
            visitors = simultaneousQueueCase();
        } else if (mode == 1) {
            visitors = repeatedVisitCase();
        } else if (mode == 2) {
            visitors = crossingRoutesCase();
        } else if (mode == 3) {
            visitors = staggeredCase();
        } else {
            visitors = boundaryTimeCase();
        }

        int m = 1;
        for (const Visitor& visitor : visitors) {
            for (int office : visitor.offices) {
                m = max(m, office);
            }
        }
        m = rnd.next(m, min(1000, m + 3));

        printCase(visitors, m);
    }

    return 0;
}
