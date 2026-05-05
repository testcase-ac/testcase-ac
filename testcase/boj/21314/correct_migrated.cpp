#include<iostream>
#include<string>
using namespace std;

pair<string, string> ans;
string str;

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
	cin >> str;
	int cnt = 0;
	for(char c : str){
		if(c == 'M') cnt++;
		else{
			ans.first += '5';
			for(int i = 0; i < cnt; i++) ans.first += '0';
			if(cnt > 0) ans.second += '1';
			for(int i = 0; i < cnt-1; i++) ans.second += '0';
			ans.second += '5';
			cnt = 0;
		}
	}
    if(cnt > 0){
        ans.first += '1';
        ans.second += '1';
        for(int i = 0; i < cnt-1; i++){
            ans.first += '1';
            ans.second += '0';
        } 
    }
	cout << ans.first << '\n' << ans.second;
}
