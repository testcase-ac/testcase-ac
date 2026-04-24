/**
 * name:    
 * solved:  N
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>
#include<tuple>

#define PRE_PROC ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); 
using namespace std;

int aeiou;
int n,m;
string src, dst;
bool is_aeiou(char ch) {
    return (ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u');
}
void func(int lv, int st){
    if(lv==m){
        aeiou = 0;
        for(int i=0; i<m; i++){
            if(is_aeiou(dst[i])) aeiou++;
        }

        if(aeiou<1 || m-aeiou<2) return;
        for(int i=0;i<m;i++){
            cout << dst[i];
        }
        cout << '\n';
        return;
    }

    for(int i=st; i<n; i++){
        dst[lv] = src[i];
        func(lv+1, i+1);
    }
}
int main(void){
    PRE_PROC
    cin >> m >> n;
    src.resize(n);
    for(int i=0; i<n; i++) {
        cin >> src[i];
    }
    sort(src.begin(), src.end(), less<int>());
    func(0, 0);
    return 0;
}