#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]){
    // Register testlib generator
    registerGen(argc, argv, 1);

    // We'll generate a grid of size N x N.
    // To keep the test small and human‐readable, choose N between 5 and 10.
    int N = rnd.next(5, 10);

    // Choose a land probability in percent.
    // This hyperparameter controls how “dense” the 1's (land) will be.
    // Here we choose an integer percent between 30% and 50% and convert to a fraction.
    int landPercent = rnd.next(30, 50);
    double p = landPercent / 100.0;

    // Create a grid and fill each cell with 1 (land) with probability p, else 0 (water)
    vector<vector<int>> grid(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (rnd.next(0.0, 1.0) < p)
                grid[i][j] = 1;
            else
                grid[i][j] = 0;
        }
    }

    // To guarantee that the input contains at least two islands, 
    // force two seeds in opposite corners.
    grid[0][0] = 1;
    grid[N-1][N-1] = 1;

    // We'll now count the number of separate islands (connected components)
    // using a DFS.
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    auto inside = [&](int i, int j)->bool {
        return (i >= 0 && i < N && j >= 0 && j < N);
    };
    auto dfs = [&](int si, int sj, auto &dfs_ref) -> void {
        stack<pair<int,int>> st;
        st.push({si, sj});
        visited[si][sj] = true;
        while(!st.empty()){
            auto [ci, cj] = st.top();
            st.pop();
            int di[4] = {1,-1,0,0};
            int dj[4] = {0,0,1,-1};
            for (int k = 0; k < 4; k++){
                int ni = ci + di[k], nj = cj + dj[k];
                if(inside(ni, nj) && !visited[ni][nj] && grid[ni][nj]==1){
                    visited[ni][nj] = true;
                    st.push({ni, nj});
                }
            }
        }
    };

    int compCount = 0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if(grid[i][j]==1 && !visited[i][j]){
                compCount++;
                dfs(i, j, dfs);
            }
        }
    }

    // If there is only one island, try to force in a new isolated island.
    if(compCount < 2){
        bool added = false;
        // Attempt to find an isolated water cell.
        for (int i = 0; i < N && !added; i++){
            for (int j = 0; j < N && !added; j++){
                if(grid[i][j] == 0){
                    bool hasLandNeighbor = false;
                    int di[4] = {1,-1,0,0};
                    int dj[4] = {0,0,1,-1};
                    for (int k = 0; k < 4; k++){
                        int ni = i + di[k], nj = j + dj[k];
                        if(inside(ni, nj) && grid[ni][nj] == 1){
                            hasLandNeighbor = true;
                            break;
                        }
                    }
                    if(!hasLandNeighbor){
                        grid[i][j] = 1;
                        added = true;
                        break;
                    }
                }
            }
        }
        // Fallback: if no isolated water cell found.
        if(!added){
            int i = 0, j = N - 1;
            grid[i][j] = 1;
            // Clear the four neighbors to ensure isolation.
            if(inside(i - 1, j)) grid[i - 1][j] = 0;
            if(inside(i + 1, j)) grid[i + 1][j] = 0;
            if(inside(i, j - 1)) grid[i][j - 1] = 0;
            if(inside(i, j + 1)) grid[i][j + 1] = 0;
        }
    }

    // Print the final test case:
    // First line: N
    // Next N lines: N numbers (0 or 1) separated by a single space.
    println(N);
    for (int i = 0; i < N; i++){
        string outLine;
        for (int j = 0; j < N; j++){
            outLine += to_string(grid[i][j]);
            if(j + 1 < N)
                outLine += " ";
        }
        println(outLine);
    }
    return 0;
}
