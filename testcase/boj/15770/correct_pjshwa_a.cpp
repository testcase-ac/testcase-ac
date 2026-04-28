#include <bits/stdc++.h>
using namespace std;

int len[20001];
char str[100005];
vector<char> v;
int cnt = 0;

int main(){
    int n;
    scanf("%d",&n);
    scanf("%s", str);
    int m = 0;
    for(int i=0;i<n;i++){
        if(str[i] == '-'){
            for(int j=0;j<2*m;j++){
                if(len[j] >= (m-1) * 2){
                    cnt--;
                    len[j] -= 2;
                }
            }
            len[2*m-2] = 0;
            len[2*m-3] = 0;
            m--;
            v.pop_back();
        }else{
            v.push_back(str[i]);
            if(m>0){
                if(v[m-1] == v[m]){
                    len[2*m-1] = 2*m+1;
                    cnt++;
                }else{
                    len[2*m-1] = 2*m-1;
                }
            }
            len[2*m] = 2*m;
            cnt++;
            for(int j=0;j<=2*m-2;j+=2){
                if(len[j] == 2*m-2){
                    if(j - m >= 0){
                        if(v[j-m] == v[m]){
                            len[j] = 2*m;
                            cnt++;
                        }
                    }
                }
            }
            for(int j=1;j<=2*m-3;j+=2){
                if(len[j] == 2*m-1){
                    if(j - m >= 0){
                        if(v[j-m] == v[m]){
                            len[j] = 2*m+1;
                            cnt++;
                        }
                    }
                }
            }
            m += 1;
        }
        printf("%d ", cnt);
    }
    printf("\n");
}
