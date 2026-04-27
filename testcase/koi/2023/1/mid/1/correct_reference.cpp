#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;
 
vector<vector<int> > rotate(const vector<vector<int> > &A) {
 
    int n = (int)A.size();
 
    vector<vector<int> > ans = vector<vector<int>  > (n);
 
    for(int i = 0; i < n; i++) {
        ans[i] = vector<int> (i+1);
    }
 
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= i; j++) {
            ans[i][j] = A[n-1-j][i-j];
        }
    }
 
    return ans;
}
 
vector<vector<int> > reflect(const vector<vector<int> > &A) {
 
    int n = (int)A.size();
 
    vector<vector<int> > ans = vector<vector<int>  > (n);
 
    for(int i = 0; i < n; i++) {
        ans[i] = vector<int> (i+1);
    }
 
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= i; j++) {
            ans[i][j] = A[i][i-j];
        }
    }
 
    return ans;
}
 
int get_diff(const vector<vector<int> > &A, const vector<vector<int> > &B) {
 
    int n = (int)A.size();
 
    int res = 0;
 
    for(int i = 0; i < n; i++) {
 
        for(int j = 0; j <= i; j++) {
            res += (A[i][j]^B[i][j]);
        }
 
    }
 
    return res;
}
 
int main()
{
    int n;
 
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    cin>>n;
 
    vector<vector<int> > A = vector<vector<int> > (n);
    vector<vector<int> > B = vector<vector<int> > (n);
 
    for(int i = 0; i < n;i++) {
        for(int j = 0; j <= i; j++) {
            int x;
            cin>>x;
            A[i].push_back(x);
        }
    }
 
    for(int i = 0; i < n;i++) {
        for(int j = 0; j <= i; j++) {
            int x;
            cin>>x;
            B[i].push_back(x);
        }
    }
 
    vector<vector<int> > tri0 = A;
    vector<vector<int> > tri1 = rotate(tri0);
    vector<vector<int> > tri2 = rotate(tri1);
    vector<vector<int> > tri3 = reflect(A);
    vector<vector<int> > tri4 = rotate(tri3);
    vector<vector<int> > tri5 = rotate(tri4);
 
    int res = get_diff(tri0, B);
 
    res = min(res, get_diff(tri1, B));
    res = min(res, get_diff(tri2, B));
    res = min(res, get_diff(tri3, B));
    res = min(res, get_diff(tri4, B));
    res = min(res, get_diff(tri5, B));
 
    cout<<res<<"\n";
 
    return 0;
}
