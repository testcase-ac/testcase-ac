#include<iostream>
#include<string>
using namespace std;

int r, c;
bool vst[25][25][2];
string arr[25], ans = "{";

int main(){
	cin >> r >> c;
	for(int i = 0; i < r; i++) cin >> arr[i];
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
            if(arr[i][j] == '#') continue;
            if(!vst[i][j][0]){
                string res = "";
				res += arr[i][j];
				vst[i][j][0] = 1;
				int x = i,y = j;
				while(1){
					y++;
					if(y >= c || arr[x][y] == '#') break;
					res += arr[x][y];
					vst[x][y][0] = 1;
				}
				if(res.size() >= 2) ans = min(ans, res);
            }
            if(!vst[i][j][1]){
                string res = "";
				res += arr[i][j];
				vst[i][j][1] = 1;
				int x = i,y = j;
				while(1){
					x++;
					if(x >= r || arr[x][y] == '#') break;
					res += arr[x][y];
					vst[x][y][1] = 1;
				}
				if(res.size() >= 2) ans = min(ans, res);
            }
		}
	}
	cout << ans;
}
