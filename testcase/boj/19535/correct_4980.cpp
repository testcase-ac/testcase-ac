#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define int long long
int A(int v);
int B(int v);
int C(int v);
int D(int v);
int E(int v);
int F(int v);
int N;
vector< vector<int> > VV;
int ncr(int n, int r) {
	if(n < r)
		return 0;
	if(r == 2) {
		return n*(n-1)/2;
	}
	if(r == 3) {
		return n*(n-1)*(n-2)/6;
	}
	throw "out of bound";
}
vector<int> cacheA;
int A(int v) {
    if (cacheA[v] != -1) {
        return cacheA[v];
    }
    cacheA[v] = ncr(VV[v].size(), 3);
    return cacheA[v];
}
vector<int> cacheB;
int B(int v) {
    if (cacheB[v] != -1) {
        return cacheB[v];
    }
    int sum = 0;
    for (int i : VV[v]) {
        sum += E(i);
    }
    cacheB[v] = sum;
    return cacheB[v];
}
vector<int> cacheC;
int C(int v) {
    if (cacheC[v] != -1) {
        return cacheC[v];
    }
    cacheC[v] = F(v)*(VV[v].size()-1);
    return cacheC[v];
}
vector<int> cacheD;
int D(int v) {
    if (cacheD[v] != -1) {
        return cacheD[v];
    }
    int sum = 0;
    for (int i : VV[v]) {
        sum += F(i);
    }
    cacheD[v] = sum;
    return cacheD[v];
}
vector<int> cacheE;
int E(int v) {
    if (cacheE[v] != -1) {
        return cacheE[v];
    }
    cacheE[v] = ncr(VV[v].size(), 2);
    return cacheE[v];
}
vector<int> cacheF;
int F(int v) {
    if (cacheF[v] != -1) {
        return cacheF[v];
    }
    int sum = 0;
    for (int i : VV[v]) {
        sum += VV[i].size();
    }
    cacheF[v] = sum;
    return cacheF[v];
}
vector< vector<int> > transf(int N, vector< vector<int> > &G);
void transform_rec(vector< vector<int> > &F, int parent, int node, vector< vector<int> > &G);
vector< vector<int> > transf(int N, vector< vector<int> > &G) {
    vector< vector<int> > F = vector< vector<int> >(N);
    transform_rec(F, -1, 0, G);
    return F;
}
int depth = 0;
void transform_rec(vector< vector<int> > &F, int parent, int node, vector< vector<int> > &G) {
    for (int i = 0 ; i < G[node].size(); i++) {
        int x = G[node][i];
        if (x != parent) {
            F[node].push_back(x);
        }
    }
    for (int i = 0 ; i < G[node].size(); i++) {
        int x = G[node][i];
        if (x != parent) {
            transform_rec(F, node, x, G);
        }
    }
}
string solve(int N, vector< vector<int> > Gr) {
    VV = transf(N,Gr);
    int dd = 0;
    for (int i = 0 ; i < N; i++) {
        dd += C(i) + D(i);
    }
    int gg = 0;
    for (int i = 0 ; i < N; i++) {
        gg += A(i) + B(i);
    }
    if (dd > gg*3) {
        return "D";
    } else if (dd < gg*3) {
        return "G";
    } else {
        return "DUDUDUNGA";
    }
}
signed main() {
    cin>>N;
    int left, right;
    vector< vector<int> > Gr(N);
    for (int i = 0 ; i < N-1 ; i++) {
        cin>>left>>right;
        left -= 1;
        right -= 1;
        Gr[left].push_back(right);
        Gr[right].push_back(left);
    }
    cacheA.resize(N, -1);
    cacheB.resize(N, -1);
    cacheC.resize(N, -1);
    cacheD.resize(N, -1);
    cacheE.resize(N, -1);
    cacheF.resize(N, -1);
    cout<<solve(N, Gr);
    return 0;
}
