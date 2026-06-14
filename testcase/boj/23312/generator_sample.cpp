#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Country {
    int first = 0;
    int v = 0;
    set<pair<int, int>> edges;

    int last() const {
        return first + v - 1;
    }
};

pair<int, int> normEdge(int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    return {a, b};
}

vector<int> components(const Country& country) {
    vector<vector<int>> graph(country.v);
    for (auto [u, v] : country.edges) {
        u -= country.first;
        v -= country.first;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> comp(country.v, -1);
    int compCount = 0;
    for (int start = 0; start < country.v; ++start) {
        if (comp[start] != -1) {
            continue;
        }
        vector<int> stack = {start};
        comp[start] = compCount;
        while (!stack.empty()) {
            int cur = stack.back();
            stack.pop_back();
            for (int next : graph[cur]) {
                if (comp[next] == -1) {
                    comp[next] = compCount;
                    stack.push_back(next);
                }
            }
        }
        ++compCount;
    }
    return comp;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 6);
    vector<Country> countries(n);

    int nextCity = 1;
    for (int i = 0; i < n; ++i) {
        countries[i].first = nextCity;
        countries[i].v = rnd.next(1, 8);
        nextCity += countries[i].v;

        vector<pair<int, int>> treeEdges;
        for (int city = 1; city < countries[i].v; ++city) {
            int parent = rnd.next(0, city - 1);
            treeEdges.push_back(normEdge(countries[i].first + city,
                                         countries[i].first + parent));
        }
        shuffle(treeEdges.begin(), treeEdges.end());

        int edgeCount = countries[i].v == 1 ? 0 : rnd.next(0, countries[i].v - 1);
        for (int j = 0; j < edgeCount; ++j) {
            countries[i].edges.insert(treeEdges[j]);
        }
    }

    vector<set<pair<int, int>>> initialEdges;
    for (const Country& country : countries) {
        initialEdges.push_back(country.edges);
    }

    int q = rnd.next(8, 24);
    vector<vector<int>> queries;
    bool hasPrint = false;

    for (int qi = 0; qi < q; ++qi) {
        int preferredType = (qi == q - 1 && !hasPrint) ? 1 : rnd.next(1, 3);

        if (preferredType == 1) {
            int k = rnd.next(1, n);
            queries.push_back({1, k});
            hasPrint = true;
            continue;
        }

        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        shuffle(order.begin(), order.end());

        bool emitted = false;
        for (int idx : order) {
            Country& country = countries[idx];

            if (preferredType == 2 && !country.edges.empty()) {
                int pick = rnd.next(static_cast<int>(country.edges.size()));
                auto it = country.edges.begin();
                advance(it, pick);
                auto [u, v] = *it;
                country.edges.erase(it);
                queries.push_back({2, u, v});
                emitted = true;
                break;
            }

            if (preferredType == 3 && country.v >= 2) {
                vector<int> comp = components(country);
                vector<pair<int, int>> candidates;
                for (int a = country.first; a <= country.last(); ++a) {
                    for (int b = a + 1; b <= country.last(); ++b) {
                        if (comp[a - country.first] != comp[b - country.first]) {
                            candidates.push_back({a, b});
                        }
                    }
                }
                if (!candidates.empty()) {
                    auto [u, v] = rnd.any(candidates);
                    country.edges.insert(normEdge(u, v));
                    queries.push_back({3, u, v});
                    emitted = true;
                    break;
                }
            }
        }

        if (!emitted) {
            int k = rnd.next(1, n);
            queries.push_back({1, k});
            hasPrint = true;
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        const Country& country = countries[i];
        println(country.v, static_cast<int>(initialEdges[i].size()));
        for (auto [u, v] : initialEdges[i]) {
            println(u, v);
        }
    }
    println(static_cast<int>(queries.size()));
    for (const vector<int>& query : queries) {
        println(query);
    }

    return 0;
}
