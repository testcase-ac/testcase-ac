#include "testlib.h"
#include <vector>
#include <string>
#include <queue>
using namespace std;

bool is_block(char c) {
    return c=='|' || c=='-' || c=='+' || c=='1' || c=='2' || c=='3' || c=='4';
}

int maskOf(char c) {
    // dir order: 0=Up,1=Right,2=Down,3=Left
    switch (c) {
        case '|': return (1<<0) | (1<<2);
        case '-': return (1<<1) | (1<<3);
        case '+': return (1<<0) | (1<<1) | (1<<2) | (1<<3);
        case '1': return (1<<1) | (1<<2); // Right, Down
        case '2': return (1<<0) | (1<<1); // Up, Right
        case '3': return (1<<0) | (1<<3); // Up, Left
        case '4': return (1<<2) | (1<<3); // Down, Left
        default: return 0;
    }
}

int opp(int d){ return (d+2)&3; }

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int R = inf.readInt(1, 25, "R");
    inf.readSpace();
    int C = inf.readInt(1, 25, "C");
    inf.readEoln();

    vector<string> grid(R);
    int cntM = 0, cntZ = 0;
    pair<int,int> posM(-1,-1), posZ(-1,-1);

    for (int i = 0; i < R; i++) {
        string row = inf.readToken("[\\.\\|\\-\\+1234MZ]+", "row");
        ensuref((int)row.size() == C, "Row %d length must be %d but got %d", i+1, C, (int)row.size());
        inf.readEoln();
        grid[i] = row;
        for (int j = 0; j < C; j++) {
            char c = row[j];
            if (c == 'M') { cntM++; posM = {i,j}; }
            else if (c == 'Z') { cntZ++; posZ = {i,j}; }
            else {
                ensuref(c=='.' || is_block(c), "Invalid character '%c' at (%d,%d)", c, i+1, j+1);
            }
        }
    }

    ensuref(cntM == 1, "There must be exactly one 'M', found %d", cntM);
    ensuref(cntZ == 1, "There must be exactly one 'Z', found %d", cntZ);

    auto neigh_blocks = [&](int x, int y) {
        int cnt = 0;
        const int dx[4] = {-1,1,0,0};
        const int dy[4] = {0,0,-1,1};
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
            if ( is_block(grid[nx][ny]) ) cnt++;
        }
        return cnt;
    };

    int mb = neigh_blocks(posM.first, posM.second);
    int zb = neigh_blocks(posZ.first, posZ.second);

    ensuref(mb == 1, "Cell 'M' at (%d,%d) must have exactly one adjacent block, found %d", posM.first+1, posM.second+1, mb);
    ensuref(zb == 1, "Cell 'Z' at (%d,%d) must have exactly one adjacent block, found %d", posZ.first+1, posZ.second+1, zb);

    // Now check the global guarantees by attempting to restore exactly one missing block.
    const int dr[4] = {-1,0,1,0};
    const int dc[4] = {0,1,0,-1};
    vector<char> cand = {'|','-','+','1','2','3','4'};

    int totalBlocks = 0;
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            if (is_block(grid[i][j])) totalBlocks++;

    auto validFinal = [&](int rr, int cc, char ch)->bool{
        if (grid[rr][cc] != '.') return false;
        vector<string> g = grid;
        g[rr][cc] = ch;

        // Count degree into M and Z from adjacent blocks
        auto endpointDeg = [&](pair<int,int> p){
            int r = p.first, c = p.second; int deg = 0; pair<int,int> last = {-1,-1};
            for (int d=0; d<4; ++d){
                int nr=r+dr[d], nc=c+dc[d];
                if (nr<0||nr>=R||nc<0||nc>=C) continue;
                if (is_block(g[nr][nc])){
                    if (maskOf(g[nr][nc]) & (1<<opp(d))){ deg++; last={nr,nc}; }
                }
            }
            return make_pair(deg,last);
        };

        auto md = endpointDeg(posM);
        auto zd = endpointDeg(posZ);
        if (md.first != 1 || zd.first != 1) return false;

        // Every pipe side must be matched by a compatible neighbor or endpoint
        for (int r=0; r<R; ++r){
            for (int c=0; c<C; ++c){
                if (!is_block(g[r][c])) continue;
                int m = maskOf(g[r][c]);
                for (int d=0; d<4; ++d){
                    if (!(m & (1<<d))) continue;
                    int nr=r+dr[d], nc=c+dc[d];
                    if (nr<0||nr>=R||nc<0||nc>=C) return false; // open to outside
                    char nb = g[nr][nc];
                    if (is_block(nb)){
                        if (!(maskOf(nb) & (1<<opp(d)))) return false; // neighbor doesn't connect back
                    } else if (nb=='M' || nb=='Z'){
                        // ok: connects to endpoint
                    } else {
                        return false; // open to empty cell
                    }
                }
            }
        }

        // BFS from M's adjacent block, ensure all blocks are used and Z is connected
        vector<vector<int>> vis(R, vector<int>(C, 0));
        queue<pair<int,int>> q;
        q.push(md.second);
        vis[md.second.first][md.second.second]=1;
        int seen=0;

        pair<int,int> zNeighbor = zd.second;

        while(!q.empty()){
            auto [r,c]=q.front(); q.pop();
            seen++;
            int m = maskOf(g[r][c]);
            for (int d=0; d<4; ++d){
                if (!(m & (1<<d))) continue;
                int nr=r+dr[d], nc=c+dc[d];
                if (nr<0||nr>=R||nc<0||nc>=C) continue; // shouldn't happen due to earlier check
                char nb = g[nr][nc];
                if (is_block(nb)){
                    if (maskOf(nb) & (1<<opp(d))){
                        if (!vis[nr][nc]){ vis[nr][nc]=1; q.push({nr,nc}); }
                    }
                }
            }
        }

        if (seen != totalBlocks + 1) return false; // all blocks (including inserted) must be used
        if (!vis[zNeighbor.first][zNeighbor.second]) return false; // Z must be connected to M

        return true;
    };

    int solutions = 0;
    for (int i=0;i<R;++i){
        for (int j=0;j<C;++j){
            if (grid[i][j] != '.') continue;
            for (char ch: cand){
                if (validFinal(i,j,ch)){
                    solutions++;
                    // don't early break: we must detect multiple valid solutions
                }
            }
        }
    }

    ensuref(solutions == 1, "There must be exactly one valid missing block placement, found %d", solutions);

    inf.readEof();
    return 0;
}
