#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
const int INF = 0x3c3c3c3c;
const long long INFL = 0x3c3c3c3c3c3c3c3c;
 
int N,M;
char pane[403][403];
char pane2[1203][1203];
int parent[1440003];
int size[1440003];
int calcId(int i, int j){
    return i*3*M + j;
}
int find(int p){
    if(p==parent[p]) return p;
    return parent[p] = find(parent[p]);
}
void merge(int a, int b){
    a = find(a), b = find(b);
    if(a==b) return;
    parent[a] = b;
    size[b] += size[a];
}
bool inRange(int i, int j){
    return 0 <= i && i < 3*N && 0 <= j && j < 3*M;
}
 
int main() {
    for(int i = 0 ; i < 1440003; i++) parent[i] = i, size[i] = 1;
    scanf("%d%d", &N, &M);
    for(int i = 0 ; i < N ; i++){
        scanf("%s",pane[i]);
    }
 
    for(int i = 0 ; i < 3*N; i++){
        for(int j = 0 ; j < 3*M; j++){
            pane2[i][j] = pane[i%N][j%M];
        }
    }
 
    for(int i = 0 ; i < 3*N; i++){
        for(int j = 0 ; j < 3*M; j++){
            for(int k = 0 ; k < 4; k++){
                int ni = (i+"1201"[k]-'1'+3*N)%(3*N);
                int nj = (j+"2110"[k]-'1'+3*M)%(3*M);
                if(!inRange(ni, nj) || pane2[i][j] != pane2[ni][nj]) continue;
                merge(calcId(i, j), calcId(ni, nj));
            }
        }
    }
    for(int i = N; i < 2*N; i++){
        for(int j = M; j < 2*M; j++){
            for(int k = 0 ; k < 8; k++){
                int ni = i+("12010202"[k]-'1')*N;
                int nj = j+("21100022"[k]-'1')*M;
                if(find( calcId(i, j) ) == find( calcId(ni, nj) )) size[find(calcId(i, j))] = -1; 
            }
        }
    }
 
    for(int i = N; i < 2*N; i++){
        for(int j = M; j < 2*M; j++){
            printf("%d ",size[find(calcId(i, j))]);
        }
        printf("\n");
    }
    return 0;
}
 

