#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    string type;
    int u;
    int v;
    int cost;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> discounted = {
        "Mugunghwa",
        "ITX-Saemaeul",
        "ITX-Cheongchun",
    };
    const vector<string> halfDiscounted = {
        "S-Train",
        "V-Train",
    };
    const vector<string> fullFare = {
        "Subway",
        "Bus",
        "Taxi",
        "Airplane",
        "KTX",
    };

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 10);
    int r;
    if (mode == 0) {
        r = rnd.next(1, 40);
    } else if (mode == 1) {
        r = rnd.next(5000, 100000);
    } else {
        r = rnd.next(20, 20000);
    }

    vector<string> cities;
    for (int i = 0; i < n; ++i) {
        cities.push_back("City" + string(1, char('A' + i)));
    }

    vector<Edge> edges;
    for (int i = 0; i + 1 < n; ++i) {
        string type;
        if (mode == 0) {
            type = rnd.any(discounted);
        } else if (mode == 1) {
            type = rnd.any(fullFare);
        } else if (mode == 2) {
            type = rnd.any(halfDiscounted);
        } else {
            int choice = rnd.next(0, 2);
            type = choice == 0 ? rnd.any(discounted) : (choice == 1 ? rnd.any(halfDiscounted) : rnd.any(fullFare));
        }
        edges.push_back({type, i, i + 1, rnd.next(1, mode == 1 ? 100000 : 5000)});
    }

    int extraBudget = rnd.next(0, min(18, n * (n - 1) / 2));
    vector<pair<int, int>> pairs;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            pairs.push_back({i, j});
        }
    }
    shuffle(pairs.begin(), pairs.end());

    for (int i = 0; i < (int)pairs.size() && extraBudget > 0; ++i, --extraBudget) {
        int bucket = rnd.next(0, 2);
        string type = bucket == 0 ? rnd.any(discounted) : (bucket == 1 ? rnd.any(halfDiscounted) : rnd.any(fullFare));
        int cost = rnd.next(1, bucket == 2 ? 100000 : 20000);
        edges.push_back({type, pairs[i].first, pairs[i].second, cost});

        if (rnd.next(0, 4) == 0) {
            string alternate = rnd.any(fullFare);
            edges.push_back({alternate, pairs[i].first, pairs[i].second, rnd.next(1, 100000)});
        }
    }

    shuffle(edges.begin(), edges.end());

    int m = rnd.next(2, min(20, 2 * n + 6));
    vector<int> plan;
    if (mode == 3) {
        int center = rnd.next(0, n - 1);
        for (int i = 0; i < m; ++i) {
            plan.push_back(i % 2 == 0 ? center : rnd.next(0, n - 1));
        }
    } else {
        int cur = rnd.next(0, n - 1);
        for (int i = 0; i < m; ++i) {
            plan.push_back(cur);
            if (rnd.next(0, 3) != 0) {
                cur = rnd.next(0, n - 1);
            }
        }
    }

    println(n, r);
    println(cities);
    println(m);
    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << cities[plan[i]];
    }
    cout << '\n';
    println((int)edges.size());
    for (const Edge& edge : edges) {
        println(edge.type, cities[edge.u], cities[edge.v], edge.cost);
    }

    return 0;
}
