#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin>>n>>m;
    char a[50000], b[50000];
    cin>>a>>b;

    int result[100000];

    for (int i = 0 ; i < m ; i++) {
        for (int j = 0 ; j < n ; j ++) {
            int temp = (a[n-1-j]-'0') * (b[m-1-i]-'0'); //문자에서 '0'을 빼면 숫자와 동일
            result[n+m-1-i-j] += temp;  
        }
    }

    for (int i = n+m-1 ; i > 0 ; i--) {
        result[i-1] += result[i] / 10;
        result[i] %= 10; 
    }

    bool flag = false;
    for (int i = 0 ; i < n+m ; i++) {
        if (!flag) {
            if (result[i] != 0)
                flag = true;
            else if (i == n+m-1)
                cout<<"0";
        }
        if (flag)
            cout<<result[i];
    }
    return 0;
}
//ㄷㄷ
