#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

void addUnique(vector<int>& values, int x) {
    if (find(values.begin(), values.end(), x) == values.end()) {
        values.push_back(x);
    }
}

void addClient(vector<vector<int>>& lists, vector<bool>& clientSeen, int list, int client) {
    addUnique(lists[list], client);
    clientSeen[client] = true;
}

void addListEdge(vector<vector<int>>& lists, int from, int to) {
    addUnique(lists[from], to);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int l;
    int clients;
    if (mode == 0) {
        l = rnd.next(1, 4);
        clients = rnd.next(1, 8);
    } else if (mode == 5) {
        l = rnd.next(8, 14);
        clients = rnd.next(8, 18);
    } else {
        l = rnd.next(3, 10);
        clients = rnd.next(3, 14);
    }
    int n = l + clients;

    vector<vector<int>> lists(l + 1);
    vector<bool> clientSeen(n + 1, false);

    if (mode == 0) {
        for (int i = 1; i <= l; ++i) {
            int cnt = rnd.next(1, min(clients, 4));
            for (int j = 0; j < cnt; ++j) {
                addClient(lists, clientSeen, i, l + rnd.next(1, clients));
            }
        }
    } else if (mode == 1) {
        for (int i = 1; i < l; ++i) addListEdge(lists, i, i + 1);
        for (int i = 1; i <= l; ++i) {
            if (rnd.next(0, 2) != 0) {
                addClient(lists, clientSeen, i, l + rnd.next(1, clients));
            }
        }
        addClient(lists, clientSeen, l, l + rnd.next(1, clients));
    } else if (mode == 2) {
        int shared = rnd.next(2, l);
        for (int i = 1; i < shared; ++i) addListEdge(lists, i, shared);
        for (int i = shared; i <= l; ++i) {
            int cnt = rnd.next(1, min(clients, 5));
            for (int j = 0; j < cnt; ++j) {
                addClient(lists, clientSeen, i, l + rnd.next(1, clients));
            }
        }
        for (int i = 1; i < shared; ++i) {
            if (rnd.next(0, 1)) addClient(lists, clientSeen, i, l + rnd.next(1, clients));
        }
    } else if (mode == 3) {
        for (int i = 1; i <= l; ++i) {
            for (int j = i + 1; j <= l; ++j) {
                if (rnd.next(0, 99) < 55) addListEdge(lists, i, j);
            }
            int cnt = rnd.next(1, min(clients, 6));
            for (int j = 0; j < cnt; ++j) {
                addClient(lists, clientSeen, i, l + rnd.next(1, clients));
            }
        }
    } else if (mode == 4) {
        vector<int> order(l);
        iota(order.begin(), order.end(), 1);
        shuffle(order.begin(), order.end());
        vector<int> pos(l + 1);
        for (int i = 0; i < l; ++i) pos[order[i]] = i;

        for (int a = 1; a <= l; ++a) {
            for (int b = 1; b <= l; ++b) {
                if (pos[a] < pos[b] && rnd.next(0, 99) < 30) addListEdge(lists, a, b);
            }
        }
        for (int i = 1; i <= l; ++i) {
            int cnt = rnd.next(0, min(clients, 4));
            for (int j = 0; j < cnt; ++j) {
                addClient(lists, clientSeen, i, l + rnd.next(1, clients));
            }
        }
    } else {
        for (int i = 1; i <= l; ++i) {
            for (int j = i + 1; j <= l; ++j) {
                if (rnd.next(0, 99) < 75) addListEdge(lists, i, j);
            }
        }
        int hotClients = rnd.next(1, min(clients, 4));
        for (int i = 1; i <= l; ++i) {
            for (int c = 1; c <= hotClients; ++c) {
                if (rnd.next(0, 99) < 65) addClient(lists, clientSeen, i, l + c);
            }
            if (rnd.next(0, 1)) addClient(lists, clientSeen, i, l + rnd.next(1, clients));
        }
    }

    for (int client = l + 1; client <= n; ++client) {
        if (!clientSeen[client]) addClient(lists, clientSeen, rnd.next(1, l), client);
    }

    for (int i = 1; i <= l; ++i) {
        if (lists[i].empty()) addClient(lists, clientSeen, i, l + rnd.next(1, clients));
        shuffle(lists[i].begin(), lists[i].end());
    }

    println(n, l);
    for (int i = 1; i <= l; ++i) {
        printf("%d", static_cast<int>(lists[i].size()));
        for (int x : lists[i]) printf(" %d", x);
        printf("\n");
    }

    return 0;
}
