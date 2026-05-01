#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

int R, C, N;
vector<string> cave;
vector<int> heights;

const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

bool inside(int r, int c) {
    return 0 <= r && r < R && 0 <= c && c < C;
}

void bfs(int r, int c, vector<vector<bool>> &visited, vector<pair<int,int>> &cluster) {
    queue<pair<int,int>> q;
    q.push({r,c});
    visited[r][c] = true;
    cluster.push_back({r,c});
    while (!q.empty()) {
        pair<int,int> curr = q.front(); q.pop();
        int rr = curr.first, cc = curr.second;
        for (int d = 0; d < 4; d++) {
            int nr = rr + dr[d], nc = cc + dc[d];
            if (inside(nr,nc) && !visited[nr][nc] && cave[nr][nc] == 'x') {
                visited[nr][nc] = true;
                cluster.push_back({nr,nc});
                q.push({nr,nc});
            }
        }
    }
}

bool clusterTouchesFloor(const vector<pair<int,int>> &cluster) {
    for (auto &p : cluster) {
        if (p.first == R-1) return true;
    }
    return false;
}

vector<vector<pair<int,int>>> findClusters() {
    vector<vector<pair<int,int>>> clusters;
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (cave[r][c] == 'x' && !visited[r][c]) {
                vector<pair<int,int>> cluster;
                bfs(r, c, visited, cluster);
                clusters.push_back(cluster);
            }
        }
    }
    return clusters;
}

bool throwStick(int height, bool fromLeft) {
    int row = R - height;
    if (fromLeft) {
        for (int c = 0; c < C; c++) {
            if (cave[row][c] == 'x') {
                cave[row][c] = '.';
                return true;
            }
        }
    } else {
        for (int c = C-1; c >= 0; c--) {
            if (cave[row][c] == 'x') {
                cave[row][c] = '.';
                return true;
            }
        }
    }
    return false;
}

bool canClusterFall(const vector<pair<int,int>> &cluster) {
    set<pair<int,int>> clusterSet(cluster.begin(), cluster.end());
    
    int minFall = R;
    for (auto &p : cluster) {
        int r = p.first, c = p.second;
        int fall = 0;
        
        for (int nr = r + 1; nr < R; nr++) {
            if (cave[nr][c] == 'x' && clusterSet.count({nr, c}) == 0) {
                break;
            }
            fall++;
        }
        minFall = min(minFall, fall);
    }
    
    if (minFall == 0) return false;
    
    for (auto &p : cluster) {
        int newR = p.first + minFall;
        if (newR >= R) return false;
        if (cave[newR][p.second] == 'x' && clusterSet.count({newR, p.second}) == 0) {
            return false;
        }
    }
    
    bool hasSupport = false;
    for (auto &p : cluster) {
        int newR = p.first + minFall;
        if (newR == R - 1) {
            hasSupport = true;
            break;
        }
        if (newR + 1 < R && cave[newR + 1][p.second] == 'x' && clusterSet.count({newR + 1, p.second}) == 0) {
            hasSupport = true;
            break;
        }
    }
    
    return hasSupport;
}

void dropCluster(vector<pair<int,int>> &cluster) {
    set<pair<int,int>> clusterSet(cluster.begin(), cluster.end());
    
    for (auto &p : cluster) {
        cave[p.first][p.second] = '.';
    }
    
    int minFall = R;
    for (auto &p : cluster) {
        int r = p.first, c = p.second;
        int fall = 0;
        
        for (int nr = r + 1; nr < R; nr++) {
            if (cave[nr][c] == 'x') {
                break;
            }
            fall++;
        }
        minFall = min(minFall, fall);
    }
    
    for (auto &p : cluster) {
        p.first += minFall;
        cave[p.first][p.second] = 'x';
    }
}

string simulate() {
    vector<vector<pair<int,int>>> initialClusters = findClusters();
    for (auto &cluster : initialClusters) {
        if (!clusterTouchesFloor(cluster)) {
            return "Initial cave has floating cluster (size: " + to_string(cluster.size()) + ")";
        }
    }
    
    for (int i = 0; i < N; i++) {
        bool fromLeft = (i % 2 == 0);
        bool hit = throwStick(heights[i], fromLeft);
        
        if (!hit) continue;
        
        vector<vector<pair<int,int>>> clusters = findClusters();
        vector<vector<pair<int,int>>> floatingClusters;
        
        for (auto &cluster : clusters) {
            if (!clusterTouchesFloor(cluster)) {
                floatingClusters.push_back(cluster);
            }
        }
        
        if (floatingClusters.size() > 1) {
            string sizes = "";
            for (int j = 0; j < floatingClusters.size(); j++) {
                if (j > 0) sizes += ", ";
                sizes += to_string(floatingClusters[j].size());
            }
            return "Multiple clusters falling simultaneously after stick " + to_string(i+1) + " at height " + to_string(heights[i]) + " (cluster sizes: " + sizes + ")";
        }
        
        if (floatingClusters.size() == 1) {
            if (!canClusterFall(floatingClusters[0])) {
                return "Cluster cannot fall to valid position after stick " + to_string(i+1) + " at height " + to_string(heights[i]);
            }
            
            dropCluster(floatingClusters[0]);
            
            clusters = findClusters();
            for (auto &cluster : clusters) {
                if (!clusterTouchesFloor(cluster)) {
                    return "Cluster still floating after falling from stick " + to_string(i+1) + " at height " + to_string(heights[i]);
                }
            }
        }
    }
    
    return "OK";
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    R = inf.readInt(1, 100, "R");
    inf.readSpace();
    C = inf.readInt(1, 100, "C");
    inf.readEoln();

    cave.resize(R);
    for (int i = 0; i < R; i++) {
        cave[i] = inf.readLine("[.x]{" + to_string(C) + "," + to_string(C) + "}", "cave_row");
    }

    N = inf.readInt(1, 100, "N");
    inf.readEoln();

    heights = inf.readInts(N, 1, R, "heights");
    inf.readEoln();

    inf.readEof();

    string result = simulate();
    ensuref(result == "OK", "Invalid simulation: %s", result.c_str());

    return 0;
}
