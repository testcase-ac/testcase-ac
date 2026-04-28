#include <iostream>
#include <algorithm>
#define endl "\n";
using namespace std;

char map[21][21];
int ch[26];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
int r, c, Max = 1, cnt = 1;

void DFS(int y, int x)
{
	for (int i = 0; i < 4; i++)
	{
		int yy = y + dy[i];
		int xx = x + dx[i];
		
		if (yy < 1 || yy > r || xx < 1 || xx > c) continue;
		
		if (ch[map[yy][xx] - 'A'] == 0)
		{
			ch[map[yy][xx] - 'A'] = 1;
			cnt++;
			Max = max(Max, cnt);
			DFS(yy, xx);
			ch[map[yy][xx] - 'A'] = 0;
			cnt--;
		}
	}
}

void Init()
{
	cin >> r >> c;
	
	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			cin >> map[i][j];
		}
	}
	
	
}


void Solve()
{
	ch[map[1][1] - 'A'] = 1;
	DFS(1 , 1);
	cout << Max << endl;

}



int main(void) {
	ios_base::sync_with_stdio(false);
	Init();
    Solve();	
	return 0;
}