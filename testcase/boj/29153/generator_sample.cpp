#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int center_count = rnd.next(1, 7);
    vector<int> side(center_count);
    for (int i = 0; i < center_count; ++i) {
        side[i] = rnd.next(0, 1);
    }
    if (center_count >= 2) {
        side[0] = 0;
        side[1] = 1;
    }

    vector<pair<int, int>> contacts;
    for (int i = 0; i < center_count; ++i) {
        for (int j = i + 1; j < center_count; ++j) {
            if (side[i] == side[j]) continue;
            int threshold = center_count <= 3 ? 75 : 45;
            if (rnd.next(100) < threshold) {
                contacts.push_back({i, j});
            }
        }
    }

    if (center_count >= 2 && contacts.empty()) {
        int a = -1;
        int b = -1;
        for (int i = 0; i < center_count; ++i) {
            for (int j = i + 1; j < center_count; ++j) {
                if (side[i] != side[j]) {
                    a = i;
                    b = j;
                }
            }
        }
        contacts.push_back({a, b});
    }

    int next_vertex = center_count + 1;
    vector<pair<int, int>> edges;
    vector<int> degree(center_count, 0);

    for (auto [a, b] : contacts) {
        int spine = next_vertex++;
        edges.push_back({a + 1, spine});
        edges.push_back({b + 1, spine});
        ++degree[a];
        ++degree[b];
    }

    for (int center = 0; center < center_count; ++center) {
        int target_degree = rnd.next(3, 6);
        while (degree[center] < target_degree) {
            int spine = next_vertex++;
            edges.push_back({center + 1, spine});
            ++degree[center];
        }
    }

    int n = next_vertex - 1;
    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());

    for (auto& edge : edges) {
        edge.first = label[edge.first];
        edge.second = label[edge.second];
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (auto [a, b] : edges) {
        println(a, b);
    }

    return 0;
}
