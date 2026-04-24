#include <iostream>

using namespace std;

string WB[8]={"WBWBWBWB",
              "BWBWBWBW",
              "WBWBWBWB",
              "BWBWBWBW",
              "WBWBWBWB",
              "BWBWBWBW",
              "WBWBWBWB",
              "BWBWBWBW"};
              
string BW[8]={"BWBWBWBW",
              "WBWBWBWB",
              "BWBWBWBW",
              "WBWBWBWB",
              "BWBWBWBW",
              "WBWBWBWB",
              "BWBWBWBW",
              "WBWBWBWB"};



int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
	
    int n, m;
    cin>>n>>m;
    
    string a[50];
    
    for(int i=0;i<n;i++) cin>>a[i];
    
    int min=100;
    
    for(int y=0;y<=n-8;y++)
    {
        for(int x=0;x<=m-8;x++)
        {
            int cnt=0;
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    if(a[y+i][x+j]!=WB[i][j]) cnt++;
                }
            }
            if(cnt<min) min=cnt;
            
            cnt=0;
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    if(a[y+i][x+j]!=BW[i][j]) cnt++;
                }
            }
            
            if(cnt<min) min=cnt;
        }
    }
    
    cout<<min;
	
    return 0;
}