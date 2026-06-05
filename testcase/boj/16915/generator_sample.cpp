#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

struct RoomEdge {
    int a;
    int b;
};

static void addEdge(vector<RoomEdge>& edges, int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    edges.push_back({a, b});
}

static vector<int> assignmentStates(const vector<RoomEdge>& edges,
                                    const vector<int>& switchValue) {
    vector<int> states;
    states.reserve(edges.size());
    for (const RoomEdge& edge : edges) {
        states.push_back(switchValue[edge.a] == switchValue[edge.b] ? 1 : 0);
    }
    return states;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m = rnd.next(2, 12);
    vector<RoomEdge> edges;
    vector<int> states;

    if (mode == 0) {
        int len = rnd.next(2, min(m, 8));
        m = max(m, len);
        for (int i = 1; i <= len; ++i) {
            addEdge(edges, i, i == len ? 1 : i + 1);
        }
        vector<int> switchValue(m + 1);
        for (int i = 1; i <= m; ++i) {
            switchValue[i] = rnd.next(0, 1);
        }
        states = assignmentStates(edges, switchValue);
    } else if (mode == 1) {
        m = max(m, 3);
        int len = rnd.next(3, min(m, 8));
        for (int i = 1; i <= len; ++i) {
            addEdge(edges, i, i == len ? 1 : i + 1);
        }
        states.assign(edges.size(), 0);
        if (rnd.next(0, 1) == 0) {
            states[rnd.next(static_cast<int>(states.size()))] = 1;
        }
    } else if (mode == 2) {
        int center = rnd.next(1, m);
        for (int i = 1; i <= m; ++i) {
            if (i != center && rnd.next(0, 2) > 0) {
                addEdge(edges, center, i);
            }
        }
        if (edges.empty()) {
            addEdge(edges, center, center == 1 ? 2 : 1);
        }
        vector<int> switchValue(m + 1);
        for (int i = 1; i <= m; ++i) {
            switchValue[i] = rnd.next(0, 1);
        }
        states = assignmentStates(edges, switchValue);
    } else if (mode == 3) {
        int active = rnd.next(2, min(m, 6));
        int pairCount = rnd.next(2, 10);
        for (int i = 0; i < pairCount; ++i) {
            int a = rnd.next(1, active);
            int b = rnd.next(1, active - 1);
            if (b >= a) {
                ++b;
            }
            addEdge(edges, a, b);
        }
        states.resize(edges.size());
        for (int& state : states) {
            state = rnd.next(0, 1);
        }
    } else {
        m = max(m, 3);
        vector<pair<int, int>> candidates;
        for (int a = 1; a <= m; ++a) {
            for (int b = a + 1; b <= m; ++b) {
                candidates.push_back({a, b});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int edgeCount = rnd.next(2, min<int>(16, candidates.size()));
        for (int i = 0; i < edgeCount; ++i) {
            addEdge(edges, candidates[i].first, candidates[i].second);
        }
        vector<int> switchValue(m + 1);
        for (int i = 1; i <= m; ++i) {
            switchValue[i] = rnd.next(0, 1);
        }
        states = assignmentStates(edges, switchValue);
        if (!states.empty() && rnd.next(0, 3) == 0) {
            int index = rnd.next(static_cast<int>(states.size()));
            states[index] ^= 1;
        }
    }

    while (edges.size() < 2) {
        int a = rnd.next(1, m);
        int b = rnd.next(1, m - 1);
        if (b >= a) {
            ++b;
        }
        addEdge(edges, a, b);
        states.push_back(rnd.next(0, 1));
    }

    vector<int> order(edges.size());
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());

    vector<RoomEdge> shuffledEdges;
    vector<int> shuffledStates;
    shuffledEdges.reserve(edges.size());
    shuffledStates.reserve(states.size());
    for (int index : order) {
        shuffledEdges.push_back(edges[index]);
        shuffledStates.push_back(states[index]);
    }
    edges = shuffledEdges;
    states = shuffledStates;

    vector<vector<int>> switchRooms(m + 1);
    for (int room = 1; room <= static_cast<int>(edges.size()); ++room) {
        switchRooms[edges[room - 1].a].push_back(room);
        switchRooms[edges[room - 1].b].push_back(room);
    }

    println(static_cast<int>(edges.size()), m);
    println(states);
    for (int switchId = 1; switchId <= m; ++switchId) {
        shuffle(switchRooms[switchId].begin(), switchRooms[switchId].end());
        printf("%d", static_cast<int>(switchRooms[switchId].size()));
        for (int room : switchRooms[switchId]) {
            printf(" %d", room);
        }
        printf("\n");
    }

    return 0;
}
