#include <vector>
#include <iostream>
// 제 코드가 아니며, 제가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
using namespace std;

int main() {
ios_base::sync_with_stdio(false);
cin.tie(NULL);
///////////////////////////////////
int n_of_customer, muddy_time; cin >> n_of_customer >> muddy_time;
vector<int> time(1000001, 0);
int last_togi = -1;
for (int n = 0; n < n_of_customer; n++) {
    int t; cin >> t;    
    time[t] = 1;
    bool togi = false;
    for (int i = last_togi+1; i < t-1; i++) {
        if (time[i] == 0) {
            togi = true;
            last_togi = i;
            time[i] = 2;
            break;
        }
    }
    if (!togi) {cout << "fail"; return 0;}

    bool coffee = false;
    int limit_time = (last_togi>(t-muddy_time)?last_togi:(t-muddy_time));
    for (int i = limit_time; i < t; i++) {
        if (time[i] == 0) {
            coffee = true;
            time[i] = 3;
            break;
        }
    }
    if (!coffee) {cout << "fail"; return 0;}
}
cout << "success";
///////////////////////////////////
return 0;}
