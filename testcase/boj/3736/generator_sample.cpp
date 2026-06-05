#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

vector<int> shuffledJobs(int n) {
    vector<int> jobs(n);
    for (int i = 0; i < n; ++i) {
        jobs[i] = i;
    }
    shuffle(jobs.begin(), jobs.end());
    return jobs;
}

vector<vector<int>> makeGraph(int n, int mode) {
    vector<vector<int>> adj(n);

    if (mode == 0) {
        int shared = n + rnd.next(n);
        for (int i = 0; i < n; ++i) {
            adj[i].push_back(shared);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            adj[i].push_back(n + i);
            if (n > 1 && rnd.next(2) == 1) {
                adj[i].push_back(n + ((i + 1) % n));
            }
        }
    } else if (mode == 2) {
        int usedServers = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            int degree = rnd.next(0, usedServers);
            vector<int> servers;
            for (int s = 0; s < usedServers; ++s) {
                servers.push_back(n + s);
            }
            shuffle(servers.begin(), servers.end());
            servers.resize(degree);
            sort(servers.begin(), servers.end());
            adj[i] = servers;
        }
    } else {
        int maxDegree = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            int degree = rnd.next(0, maxDegree);
            set<int> servers;
            while (static_cast<int>(servers.size()) < degree) {
                servers.insert(n + rnd.next(n));
            }
            adj[i].assign(servers.begin(), servers.end());
        }
    }

    return adj;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(1, 4);
    for (int tc = 0; tc < datasets; ++tc) {
        int n = rnd.next(1, 12);
        int mode = rnd.next(4);
        vector<vector<int>> adj = makeGraph(n, mode);
        vector<int> jobs = shuffledJobs(n);

        println(n);
        for (int job : jobs) {
            printf("%d: (%d)", job, static_cast<int>(adj[job].size()));
            for (int server : adj[job]) {
                printf(" %d", server);
            }
            printf("\n");
        }
    }

    return 0;
}
