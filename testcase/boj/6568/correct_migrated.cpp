#include<iostream>
using namespace std;
int b(string s){int r=0;for(int i=0;i<8;i++)r|=(s[7-i]-'0')<<i;return r;}
int main(){int m[32],a=0,p=0;string s;bool f=1;while(cin){if(f){for(int i=0;i<32;i++){cin>>s;m[i]=b(s);}f=0;}int x=m[p++%32],o=x>>5,y=x&31;if(o==0)m[y]=a;else if(o==1)a=m[y];else if(o==2&&!a)p=y;else if(o==4)a=(a+255)%256;else if(o==5)a=(a+1)%256;else if(o==6)p=y;else if(o==7){for(int i=7;~i;i--)cout<<((a>>i)&1);cout<<'\n';a=p=0;f=1;}}}
