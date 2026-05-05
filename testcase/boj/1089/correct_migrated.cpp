#include<iostream>
#include<string>
#include<vector>
using namespace std;

double ans = 0;
int n, bulb[10] = {1168,14043,3096,1560,13842,1584,1072,14040,1040,1552};
string arr[5];

double pow(int p, int n){
    double res = 1;
    while(n--) res *= p;
    return res;
}

int main(){
	cin >> n;
	for(int i = 0; i < 5; i++) cin >> arr[i];
	for(int i = 0; i < n; i++){
		int d = 0, ds = 0;
		vector<int> vec;
		for(int j = 0; j < 5; j++){
			for(int k = 0; k < 3; k++){
				if(arr[j][i*4+k] == '#') d += (1<<(j*3+k));
			}
		}
		for(int j = 0; j < 10; j++){
			if((d&bulb[j])==0) vec.push_back(j);
		}
		if(vec.size() == 0){
			cout << -1;
			return 0;
		}
		for(int j : vec) ds += j;
        ans += (double)ds / vec.size() * pow(10, n-1-i);
	}
    cout << ans;
}
