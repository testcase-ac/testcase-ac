#include <iostream>
#include <algorithm>
using namespace std;
string mo="koiOjpuPhynbml";
string ss[11]={"rt","sw","sg","fr","fa","fq","ft","fx","fv","fg","qt"};
string ang="EQW";
bool isMo(char a){
    bool flag=false;
    for(int j=0;j<mo.length();j++){
        if(mo[j]==a){
            flag=true;break;
        }
    }
    return flag;
}
bool isJong(char a,char b){
    bool flag=false;
    for(int j=0;j<11;j++){
        if(ss[j][0]==a&&ss[j][1]==b){
            flag=true;break;
        }
    }
    return flag;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string str;
    getline(cin,str);
    long long ans=0;
    for(int i=0;i<str.length();i++){
        if(str[i]==' ')continue;
        if(!isMo(str[i]))continue;
        if(isMo(str[i-1]))continue;
        if(i-2<=0)continue;
        if(str[i-2]==' ')continue;
        if(isMo(str[i-2])){
            int tttt=1;
            for(int j=0;j<3;j++){
                if(str[i-1]==ang[j]){
                    tttt--;break;
                }
            }
            ans+=tttt;
            continue;
        }
        if(str[i-3]==' '||i-3<0)continue;
        if(!isMo(str[i-3]))continue;
        if(isJong(str[i-2],str[i-1])){
            ans++;
        }
    }
    cout<<ans;
}

// jthis - https://www.acmicpc.net/source/22405219
