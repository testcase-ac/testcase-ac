#include <bits/stdc++.h>
#define x first
#define y second
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;

typedef long long ll;

char ans[1010][1010];

void f2(int i, int j){
    ans[i][j] = '|';
    ans[i+1][j] = 'b'; ans[i+1][j+1] = '-';
}
void f6(int i, int j){
    char a[6][10] = {"|", "b-", "p-|", "||b-", "|b-||", "b--db-"};
    for(int k=0; k<6; k++){
        for(int s=0; s<=k; s++){
            ans[i+k][j+s] = a[k][s];
        }
    }
}
void f9(int i, int j){
    char a[9][10] = {
        "|",
        "b-",
        "-q|",
        "||b-",
        "b--q|",
        "p-||b-",
        "|-d-q-q",
        "p-||||||",
        "|-db-b-b-"
    };
    for(int k=0; k<9; k++){
        for(int s=0; s<=k; s++){
            ans[i+k][j+s] = a[k][s];
        }
    }
}
void sq2(int i, int j, int jj){
    char a[2][4] = {"|-q", "b-|"};
    for(int k=j; k<=jj; k+=3){
        for(int t1=0; t1<2; t1++) for(int t2=0; t2<3; t2++) ans[i+t1][k+t2] = a[t1][t2];
    }
}
void sq6(int i, int j, int jj){
    char a[2][4] = {"|-q", "b-|"};
    for(int k=i; k<i+6; k+=2){
        for(int s=j; s<=jj; s+=3){
            for(int t1=0; t1<2; t1++) for(int t2=0; t2<3; t2++) ans[k+t1][s+t2] = a[t1][t2];
        }
    }
}

void f(int i, int j, int n){
    if(n % 3 == 2){
        if(n == 2) f2(i, j);
        else f(i, j, n-2), f2(i+n-2, j+n-2), sq2(i+n-2, j, j+n-3);
    }
    if(n % 3 == 0){
        if(n == 6) f6(i, j);
        else if(n == 9) f9(i, j);
        else f(i, j, n-6), f6(i+n-6, j+n-6), sq6(i+n-6, j, j+n-7);
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    if(n % 3 == 1){ cout << "impossible"; return 0; }
    if(n == 3 || n == 5){ cout << "impossible"; return 0; }
    f(1, 1, n);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=i; j++) cout << ans[i][j];
        cout << "\n";
    }
}
