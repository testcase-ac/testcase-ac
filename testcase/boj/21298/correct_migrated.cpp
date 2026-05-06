#include <bits/stdc++.h>
#define ll long long
using namespace std;
vector<int> d={1,2,3,4,5,6,7,8,9,10,11};
void q1(vector<vector<vector<vector<vector<vector<vector<vector<vector<vector<vector<ll>>>>>>>>>>> &a,int op) {
    int m1,n1,o1,p1,q1,r1,s1,t1,u1,v1,w1,m2,n2,o2,p2,q2,r2,s2,t2,u2,v2,w2;
    cin>>m1>>n1>>o1>>p1>>q1>>r1>>s1>>t1>>u1>>v1>>w1>>m2>>n2>>o2>>p2>>q2>>r2>>s2>>t2>>u2>>v2>>w2;
    m1--;n1--;o1--;p1--;q1--;r1--;s1--;t1--;u1--;v1--;w1--;
    int k=d[op-1];
    vector<int> pp={m1,n1,o1,p1,q1,r1,s1,t1,u1,v1,w1},xx(11);
    vector<int> qq={m2,n2,o2,p2,q2,r2,s2,t2,u2,v2,w2},yy(11);
    for(int i=0;i<11;i++) {xx[d[i]-1]=pp[i];yy[d[i]-1]=qq[i];}
    m1=xx[0],n1=xx[1],o1=xx[2],p1=xx[3],q1=xx[4],r1=xx[5],s1=xx[6],t1=xx[7],u1=xx[8],v1=xx[9],w1=xx[10];
    m2=yy[0],n2=yy[1],o2=yy[2],p2=yy[3],q2=yy[4],r2=yy[5],s2=yy[6],t2=yy[7],u2=yy[8],v2=yy[9],w2=yy[10];
    if(k==1) {
        for(int i1=m1;i1<(m1+m2)/2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) swap(a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11],a[m1+m2-1-i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]);
    } else if(k==2) {
        for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<(n1+n2)/2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) swap(a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11],a[i1][n1+n2-1-i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]);
    } else if(k==3) {
        for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<(o1+o2)/2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) swap(a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11],a[i1][i2][o1+o2-1-i3][i4][i5][i6][i7][i8][i9][i10][i11]);
    } else if(k==4) {
        for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<(p1+p2)/2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) swap(a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11],a[i1][i2][i3][p1+p2-1-i4][i5][i6][i7][i8][i9][i10][i11]);
    } else if(k==5) {
        for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<(q1+q2)/2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) swap(a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11],a[i1][i2][i3][i4][q1+q2-1-i5][i6][i7][i8][i9][i10][i11]);
    } else if(k==6) {
        for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<(r1+r2)/2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) swap(a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11],a[i1][i2][i3][i4][i5][r1+r2-1-i6][i7][i8][i9][i10][i11]);
    } else if(k==7) {
        for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<(s1+s2)/2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) swap(a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11],a[i1][i2][i3][i4][i5][i6][s1+s2-1-i7][i8][i9][i10][i11]);
    } else if(k==8) {
        for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<(t1+t2)/2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) swap(a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11],a[i1][i2][i3][i4][i5][i6][i7][t1+t2-1-i8][i9][i10][i11]);
    } else if(k==9) {
        for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<(u1+u2)/2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) swap(a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11],a[i1][i2][i3][i4][i5][i6][i7][i8][u1+u2-1-i9][i10][i11]);
    } else if(k==10) {
        for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<(v1+v2)/2;i10++) for(int i11=w1;i11<w2;i11++) swap(a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11],a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+v2-1-i10][i11]);
    } else if(k==11) {
        for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<(w1+w2)/2;i11++) swap(a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11],a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+w2-1-i11]);
    }
}
void q2(vector<vector<vector<vector<vector<vector<vector<vector<vector<vector<vector<ll>>>>>>>>>>> &a,int op) {
    int m1,n1,o1,p1,q1,r1,s1,t1,u1,v1,w1,m2,n2,o2,p2,q2,r2,s2,t2,u2,v2,w2;
    cin>>m1>>n1>>o1>>p1>>q1>>r1>>s1>>t1>>u1>>v1>>w1>>m2>>n2>>o2>>p2>>q2>>r2>>s2>>t2>>u2>>v2>>w2;
    m1--;n1--;o1--;p1--;q1--;r1--;s1--;t1--;u1--;v1--;w1--;
    int k;
    for(int i=0;i<11;i++) if(d[i]==op) k=i+1;
    vector<int> pp={m1,n1,o1,p1,q1,r1,s1,t1,u1,v1,w1},xx(11);
    vector<int> qq={m2,n2,o2,p2,q2,r2,s2,t2,u2,v2,w2},yy(11);
    for(int i=0;i<11;i++) {xx[d[i]-1]=pp[i];yy[d[i]-1]=qq[i];}
    m1=xx[0],n1=xx[1],o1=xx[2],p1=xx[3],q1=xx[4],r1=xx[5],s1=xx[6],t1=xx[7],u1=xx[8],v1=xx[9],w1=xx[10];
    m2=yy[0],n2=yy[1],o2=yy[2],p2=yy[3],q2=yy[4],r2=yy[5],s2=yy[6],t2=yy[7],u2=yy[8],v2=yy[9],w2=yy[10];
    int x,y;
    if(op<22) {x=1;y=op-10;}
    else if(op<31) {x=2;y=op-19;}
    else if(op<39) {x=3;y=op-27;}
    else if(op<46) {x=4;y=op-34;}
    else if(op<52) {x=5;y=op-40;}
    else if(op<57) {x=6;y=op-45;}
    else if(op<61) {x=7;y=op-49;}
    else if(op<64) {x=8;y=op-52;}
    else if(op<66) {x=9;y=op-54;}
    else {x=10;y=11;}
    x=d[x-1];
    y=d[y-1];
    if(x==1&&y==2) {
        for(int i=0;i<min(m2-m1,n2-n1)/2;i++) {
            for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[m1+i][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1+1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2+1][i3][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1-1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2-1][i3][i4][i5][i6][i7][i8][i9][i10][i11];
                a[m1+i][n1+i+1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==1&&y==3) {
        for(int i=0;i<min(m2-m1,o2-o1)/2;i++) {
            for(int i2=n1;i2<n2;i2++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[m1+i][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1+1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2][i3+1][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1-1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2][i3-1][i4][i5][i6][i7][i8][i9][i10][i11];
                a[m1+i][i2][o1+i+1][i4][i5][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==1&&y==4) {
        for(int i=0;i<min(m2-m1,p2-p1)/2;i++) {
            for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[m1+i][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1+1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2][i3][i4+1][i5][i6][i7][i8][i9][i10][i11];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1-1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2][i3][i4-1][i5][i6][i7][i8][i9][i10][i11];
                a[m1+i][i2][i3][p1+i+1][i5][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==1&&y==5) {
        for(int i=0;i<min(m2-m1,q2-q1)/2;i++) {
            for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[m1+i][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1+1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2][i3][i4][i5+1][i6][i7][i8][i9][i10][i11];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1-1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2][i3][i4][i5-1][i6][i7][i8][i9][i10][i11];
                a[m1+i][i2][i3][i4][q1+i+1][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==1&&y==6) {
        for(int i=0;i<min(m2-m1,r2-r1)/2;i++) {
            for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[m1+i][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1+1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2][i3][i4][i5][i6+1][i7][i8][i9][i10][i11];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1-1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2][i3][i4][i5][i6-1][i7][i8][i9][i10][i11];
                a[m1+i][i2][i3][i4][i5][r1+i+1][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==1&&y==7) {
        for(int i=0;i<min(m2-m1,s2-s1)/2;i++) {
            for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[m1+i][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1+1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2][i3][i4][i5][i6][i7+1][i8][i9][i10][i11];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1-1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2][i3][i4][i5][i6][i7-1][i8][i9][i10][i11];
                a[m1+i][i2][i3][i4][i5][i6][s1+i+1][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==1&&y==8) {
        for(int i=0;i<min(m2-m1,t2-t1)/2;i++) {
            for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[m1+i][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1+1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2][i3][i4][i5][i6][i7][i8+1][i9][i10][i11];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1-1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2][i3][i4][i5][i6][i7][i8-1][i9][i10][i11];
                a[m1+i][i2][i3][i4][i5][i6][i7][t1+i+1][i9][i10][i11]=t;
            }
        } 
    } else if(x==1&&y==9) {
        for(int i=0;i<min(m2-m1,u2-u1)/2;i++) {
            for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[m1+i][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1+1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9+1][i10][i11];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1-1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9-1][i10][i11];
                a[m1+i][i2][i3][i4][i5][i6][i7][i8][u1+i+1][i10][i11]=t;
            }
        } 
    } else if(x==1&&y==10) {
        for(int i=0;i<min(m2-m1,v2-v1)/2;i++) {
            for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1+1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10+1][i11];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1-1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10-1][i11];
                a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][v1+i+1][i11]=t;
            }
        } 
    } else if(x==1&&y==11) {
        for(int i=0;i<min(m2-m1,w2-w1)/2;i++) {
            for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) {
                ll t=a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1+1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11+1];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11-1];
                a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i+1]=t;
            }
        }
    } else if(x==2&&y==1) {
        for(int i=0;i<min(n2-n1,m2-m1)/2;i++) {
            for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[m1+i][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2+1][i3][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1+1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2-1][i3][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1-1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11];
                a[m1+i+1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==2&&y==3) {
        for(int i=0;i<min(n2-n1,o2-o1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][n1+i][o1+i][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2+1][o1+i][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n2-i-1][i3+1][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2-1][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n1+i][i3-1][i4][i5][i6][i7][i8][i9][i10][i11];
                a[i1][n1+i][o1+i+1][i4][i5][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==2&&y==4) {
        for(int i=0;i<min(n2-n1,p2-p1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i3=o1;i3<o2;i3++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][n1+i][i3][p1+i][i5][i6][i7][i8][i9][i10][i11];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2+1][i3][p1+i][i5][i6][i7][i8][i9][i10][i11];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n2-i-1][i3][i4+1][i5][i6][i7][i8][i9][i10][i11];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2-1][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n1+i][i3][i4-1][i5][i6][i7][i8][i9][i10][i11];
                a[i1][n1+i][i3][p1+i+1][i5][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==2&&y==5) {
        for(int i=0;i<min(n2-n1,q2-q1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][n1+i][i3][i4][q1+i][i6][i7][i8][i9][i10][i11];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1][i2+1][i3][i4][q1+i][i6][i7][i8][i9][i10][i11];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n2-i-1][i3][i4][i5+1][i6][i7][i8][i9][i10][i11];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1][i2-1][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n1+i][i3][i4][i5-1][i6][i7][i8][i9][i10][i11];
                a[i1][n1+i][i3][i4][q1+i+1][i6][i7][i8][i9][i10][i11]=t;
            }
        } 
    } else if(x==2&&y==6) {
        for(int i=0;i<min(n2-n1,r2-r1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][n1+i][i3][i4][i5][r1+i][i7][i8][i9][i10][i11];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1][i2+1][i3][i4][i5][r1+i][i7][i8][i9][i10][i11];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n2-i-1][i3][i4][i5][i6+1][i7][i8][i9][i10][i11];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1][i2-1][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n1+i][i3][i4][i5][i6-1][i7][i8][i9][i10][i11];
                a[i1][n1+i][i3][i4][i5][r1+i+1][i7][i8][i9][i10][i11]=t;
            }
        } 
    } else if(x==2&&y==7) {
        for(int i=0;i<min(n2-n1,s2-s1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][n1+i][i3][i4][i5][i6][s1+i][i8][i9][i10][i11];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1][i2+1][i3][i4][i5][i6][s1+i][i8][i9][i10][i11];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n2-i-1][i3][i4][i5][i6][i7+1][i8][i9][i10][i11];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1][i2-1][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n1+i][i3][i4][i5][i6][i7-1][i8][i9][i10][i11];
                a[i1][n1+i][i3][i4][i5][i6][s1+i+1][i8][i9][i10][i11]=t;
            }
        } 
    } else if(x==2&&y==8) {
        for(int i=0;i<min(n2-n1,t2-t1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][n1+i][i3][i4][i5][i6][i7][t1+i][i9][i10][i11];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1][i2+1][i3][i4][i5][i6][i7][t1+i][i9][i10][i11];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n2-i-1][i3][i4][i5][i6][i7][i8+1][i9][i10][i11];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1][i2-1][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n1+i][i3][i4][i5][i6][i7][i8-1][i9][i10][i11];
                a[i1][n1+i][i3][i4][i5][i6][i7][t1+i+1][i9][i10][i11]=t;
            }
        } 
    } else if(x==2&&y==9) {
        for(int i=0;i<min(n2-n1,u2-u1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][n1+i][i3][i4][i5][i6][i7][i8][u1+i][i10][i11];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1][i2+1][i3][i4][i5][i6][i7][i8][u1+i][i10][i11];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9+1][i10][i11];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1][i2-1][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9-1][i10][i11];
                a[i1][n1+i][i3][i4][i5][i6][i7][i8][u1+i+1][i10][i11]=t;
            }
        } 
    } else if(x==2&&y==10) {
        for(int i=0;i<min(n2-n1,v2-v1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][v1+i][i11];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1][i2+1][i3][i4][i5][i6][i7][i8][i9][v1+i][i11];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10+1][i11];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1][i2-1][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10-1][i11];
                a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][v1+i+1][i11]=t;
            }
        } 
    } else if(x==2&&y==11) {
        for(int i=0;i<min(n2-n1,w2-w1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) {
                ll t=a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][w1+i];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1][i2+1][i3][i4][i5][i6][i7][i8][i9][i10][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11+1];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1][i2-1][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11-1];
                a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][w1+i+1]=t;
            }
        }
    } else if(x==3&&y==1) {
        for(int i=0;i<min(o2-o1,m2-m1)/2;i++) {
            for(int i2=n1;i2<n2;i2++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[m1+i][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2][i3+1][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1+1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2][i3-1][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1-1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11];
                a[m1+i+1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==3&&y==2) {
        for(int i=0;i<min(o2-o1,n2-n1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][n1+i][o1+i][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n1+i][i3+1][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2+1][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n2-i-1][i3-1][i4][i5][i6][i7][i8][i9][i10][i11];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2-1][o1+i][i4][i5][i6][i7][i8][i9][i10][i11];
                a[i1][n1+i+1][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==3&&y==4) {
        for(int i=0;i<min(o2-o1,p2-p1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][o1+i][p1+i][i5][i6][i7][i8][i9][i10][i11];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3+1][p1+i][i5][i6][i7][i8][i9][i10][i11];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o2-i-1][i4+1][i5][i6][i7][i8][i9][i10][i11];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3-1][p2-i-1][i5][i6][i7][i8][i9][i10][i11];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o1+i][i4-1][i5][i6][i7][i8][i9][i10][i11];
                a[i1][i2][o1+i][p1+i+1][i5][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==3&&y==5) {
        for(int i=0;i<min(o2-o1,q2-q1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i4=p1;i4<p2;i4++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][o1+i][i4][q1+i][i6][i7][i8][i9][i10][i11];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3+1][i4][q1+i][i6][i7][i8][i9][i10][i11];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o2-i-1][i4][i5+1][i6][i7][i8][i9][i10][i11];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3-1][i4][q2-i-1][i6][i7][i8][i9][i10][i11];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o1+i][i4][i5-1][i6][i7][i8][i9][i10][i11];
                a[i1][i2][o1+i][i4][q1+i+1][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==3&&y==6) {
        for(int i=0;i<min(o2-o1,r2-r1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][o1+i][i4][i5][r1+i][i7][i8][i9][i10][i11];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1][i2][i3+1][i4][i5][r1+i][i7][i8][i9][i10][i11];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o2-i-1][i4][i5][i6+1][i7][i8][i9][i10][i11];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1][i2][i3-1][i4][i5][r2-i-1][i7][i8][i9][i10][i11];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o1+i][i4][i5][i6-1][i7][i8][i9][i10][i11];
                a[i1][i2][o1+i][i4][i5][r1+i+1][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==3&&y==7) {
        for(int i=0;i<min(o2-o1,s2-s1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][o1+i][i4][i5][i6][s1+i][i8][i9][i10][i11];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1][i2][i3+1][i4][i5][i6][s1+i][i8][i9][i10][i11];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o2-i-1][i4][i5][i6][i7+1][i8][i9][i10][i11];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1][i2][i3-1][i4][i5][i6][s2-i-1][i8][i9][i10][i11];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o1+i][i4][i5][i6][i7-1][i8][i9][i10][i11];
                a[i1][i2][o1+i][i4][i5][i6][s1+i+1][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==3&&y==8) {
        for(int i=0;i<min(o2-o1,t2-t1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][o1+i][i4][i5][i6][i7][t1+i][i9][i10][i11];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1][i2][i3+1][i4][i5][i6][i7][t1+i][i9][i10][i11];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o2-i-1][i4][i5][i6][i7][i8+1][i9][i10][i11];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1][i2][i3-1][i4][i5][i6][i7][t2-i-1][i9][i10][i11];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o1+i][i4][i5][i6][i7][i8-1][i9][i10][i11];
                a[i1][i2][o1+i][i4][i5][i6][i7][t1+i+1][i9][i10][i11]=t;
            }
        }
    } else if(x==3&&y==9) {
        for(int i=0;i<min(o2-o1,u2-u1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][o1+i][i4][i5][i6][i7][i8][u1+i][i10][i11];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1][i2][i3+1][i4][i5][i6][i7][i8][u1+i][i10][i11];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9+1][i10][i11];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1][i2][i3-1][i4][i5][i6][i7][i8][u2-i-1][i10][i11];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9-1][i10][i11];
                a[i1][i2][o1+i][i4][i5][i6][i7][i8][u1+i+1][i10][i11]=t;
            }
        }
    } else if(x==3&&y==10) {
        for(int i=0;i<min(o2-o1,v2-v1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][v1+i][i11];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1][i2][i3+1][i4][i5][i6][i7][i8][i9][v1+i][i11];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10+1][i11];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1][i2][i3-1][i4][i5][i6][i7][i8][i9][v2-i-1][i11];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10-1][i11];
                a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][v1+i+1][i11]=t;
            }
        }
    } else if(x==3&&y==11) {
        for(int i=0;i<min(o2-o1,w2-w1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) {
                ll t=a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][w1+i];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1][i2][i3+1][i4][i5][i6][i7][i8][i9][i10][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11+1];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1][i2][i3-1][i4][i5][i6][i7][i8][i9][i10][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11-1];
                a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][w1+i+1]=t;
            }
        }
    } else if(x==4&&y==1) {
        for(int i=0;i<min(p2-p1,m2-m1)/2;i++) {
            for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[m1+i][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2][i3][i4+1][i5][i6][i7][i8][i9][i10][i11];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1+1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2][i3][i4-1][i5][i6][i7][i8][i9][i10][i11];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1-1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11];
                a[m1+i+1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==4&&y==2) {
        for(int i=0;i<min(p2-p1,n2-n1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i3=o1;i3<o2;i3++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][n1+i][i3][p1+i][i5][i6][i7][i8][i9][i10][i11];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n1+i][i3][i4+1][i5][i6][i7][i8][i9][i10][i11];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2+1][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n2-i-1][i3][i4-1][i5][i6][i7][i8][i9][i10][i11];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2-1][i3][p1+i][i5][i6][i7][i8][i9][i10][i11];
                a[i1][n1+i+1][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==4&&y==3) {
        for(int i=0;i<min(p2-p1,o2-o1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][o1+i][p1+i][i5][i6][i7][i8][i9][i10][i11];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o1+i][i4+1][i5][i6][i7][i8][i9][i10][i11];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3+1][p2-i-1][i5][i6][i7][i8][i9][i10][i11];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o2-i-1][i4-1][i5][i6][i7][i8][i9][i10][i11];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3-1][p1+i][i5][i6][i7][i8][i9][i10][i11];
                a[i1][i2][o1+i+1][p1+i][i5][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==4&&y==5) {
        for(int i=0;i<min(p2-p1,q2-q1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][p1+i][q1+i][i6][i7][i8][i9][i10][i11];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4+1][q1+i][i6][i7][i8][i9][i10][i11];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p2-i-1][i5+1][i6][i7][i8][i9][i10][i11];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4-1][q2-i-1][i6][i7][i8][i9][i10][i11];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p1+i][i5-1][i6][i7][i8][i9][i10][i11];
                a[i1][i2][i3][p1+i][q1+i+1][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==4&&y==6) {
        for(int i=0;i<min(p2-p1,r2-r1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i5=q1;i5<q2;i5++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][p1+i][i5][r1+i][i7][i8][i9][i10][i11];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4+1][i5][r1+i][i7][i8][i9][i10][i11];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p2-i-1][i5][i6+1][i7][i8][i9][i10][i11];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4-1][i5][r2-i-1][i7][i8][i9][i10][i11];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p1+i][i5][i6-1][i7][i8][i9][i10][i11];
                a[i1][i2][i3][p1+i][i5][r1+i+1][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==4&&y==7) {
        for(int i=0;i<min(p2-p1,s2-s1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][p1+i][i5][i6][s1+i][i8][i9][i10][i11];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1][i2][i3][i4+1][i5][i6][s1+i][i8][i9][i10][i11];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p2-i-1][i5][i6][i7+1][i8][i9][i10][i11];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1][i2][i3][i4-1][i5][i6][s2-i-1][i8][i9][i10][i11];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p1+i][i5][i6][i7-1][i8][i9][i10][i11];
                a[i1][i2][i3][p1+i][i5][i6][s1+i+1][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==4&&y==8) {
        for(int i=0;i<min(p2-p1,t2-t1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][p1+i][i5][i6][i7][t1+i][i9][i10][i11];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1][i2][i3][i4+1][i5][i6][i7][t1+i][i9][i10][i11];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p2-i-1][i5][i6][i7][i8+1][i9][i10][i11];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1][i2][i3][i4-1][i5][i6][i7][t2-i-1][i9][i10][i11];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p1+i][i5][i6][i7][i8-1][i9][i10][i11];
                a[i1][i2][i3][p1+i][i5][i6][i7][t1+i+1][i9][i10][i11]=t;
            }
        }
    } else if(x==4&&y==9) {
        for(int i=0;i<min(p2-p1,u2-u1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][p1+i][i5][i6][i7][i8][u1+i][i10][i11];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1][i2][i3][i4+1][i5][i6][i7][i8][u1+i][i10][i11];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9+1][i10][i11];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1][i2][i3][i4-1][i5][i6][i7][i8][u2-i-1][i10][i11];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9-1][i10][i11];
                a[i1][i2][i3][p1+i][i5][i6][i7][i8][u1+i+1][i10][i11]=t;
            }
        }
    } else if(x==4&&y==10) {
        for(int i=0;i<min(p2-p1,v2-v1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][v1+i][i11];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1][i2][i3][i4+1][i5][i6][i7][i8][i9][v1+i][i11];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10+1][i11];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1][i2][i3][i4-1][i5][i6][i7][i8][i9][v2-i-1][i11];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10-1][i11];
                a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][v1+i+1][i11]=t;
            }
        }
    } else if(x==4&&y==11) {
        for(int i=0;i<min(p2-p1,w2-w1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) {
                ll t=a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][w1+i];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1][i2][i3][i4+1][i5][i6][i7][i8][i9][i10][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11+1];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1][i2][i3][i4-1][i5][i6][i7][i8][i9][i10][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11-1];
                a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][w1+i+1]=t;
            }
        }
    } else if(x==5&&y==1) {
        for(int i=0;i<min(q2-q1,m2-m1)/2;i++) {
            for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[m1+i][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2][i3][i4][i5+1][i6][i7][i8][i9][i10][i11];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1+1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2][i3][i4][i5-1][i6][i7][i8][i9][i10][i11];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1-1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11];
                a[m1+i+1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==5&&y==2) {
        for(int i=0;i<min(q2-q1,n2-n1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][n1+i][i3][i4][q1+i][i6][i7][i8][i9][i10][i11];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n1+i][i3][i4][i5+1][i6][i7][i8][i9][i10][i11];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1][i2+1][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n2-i-1][i3][i4][i5-1][i6][i7][i8][i9][i10][i11];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1][i2-1][i3][i4][q1+i][i6][i7][i8][i9][i10][i11];
                a[i1][n1+i+1][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==5&&y==3) {
        for(int i=0;i<min(q2-q1,o2-o1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i4=p1;i4<p2;i4++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][o1+i][i4][q1+i][i6][i7][i8][i9][i10][i11];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o1+i][i4][i5+1][i6][i7][i8][i9][i10][i11];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3+1][i4][q2-i-1][i6][i7][i8][i9][i10][i11];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o2-i-1][i4][i5-1][i6][i7][i8][i9][i10][i11];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3-1][i4][q1+i][i6][i7][i8][i9][i10][i11];
                a[i1][i2][o1+i+1][i4][q1+i][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==5&&y==4) {
        for(int i=0;i<min(q2-q1,p2-p1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][p1+i][q1+i][i6][i7][i8][i9][i10][i11];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p1+i][i5+1][i6][i7][i8][i9][i10][i11];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4+1][q2-i-1][i6][i7][i8][i9][i10][i11];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p2-i-1][i5-1][i6][i7][i8][i9][i10][i11];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4-1][q1+i][i6][i7][i8][i9][i10][i11];
                a[i1][i2][i3][p1+i+1][q1+i][i6][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==5&&y==6) {
        for(int i=0;i<min(q2-q1,r2-r1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][q1+i][r1+i][i7][i8][i9][i10][i11];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5+1][r1+i][i7][i8][i9][i10][i11];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q2-i-1][i6+1][i7][i8][i9][i10][i11];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5-1][r2-i-1][i7][i8][i9][i10][i11];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q1+i][i6-1][i7][i8][i9][i10][i11];
                a[i1][i2][i3][i4][q1+i][r1+i+1][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==5&&y==7) {
        for(int i=0;i<min(q2-q1,s2-s1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i6=r1;i6<r2;i6++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][q1+i][i6][s1+i][i8][i9][i10][i11];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5+1][i6][s1+i][i8][i9][i10][i11];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q2-i-1][i6][i7+1][i8][i9][i10][i11];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5-1][i6][s2-i-1][i8][i9][i10][i11];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q1+i][i6][i7-1][i8][i9][i10][i11];
                a[i1][i2][i3][i4][q1+i][i6][s1+i+1][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==5&&y==8) {
        for(int i=0;i<min(q2-q1,t2-t1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][q1+i][i6][i7][t1+i][i9][i10][i11];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1][i2][i3][i4][i5+1][i6][i7][t1+i][i9][i10][i11];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q2-i-1][i6][i7][i8+1][i9][i10][i11];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1][i2][i3][i4][i5-1][i6][i7][t2-i-1][i9][i10][i11];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q1+i][i6][i7][i8-1][i9][i10][i11];
                a[i1][i2][i3][i4][q1+i][i6][i7][t1+i+1][i9][i10][i11]=t;
            }
        }
    } else if(x==5&&y==9) {
        for(int i=0;i<min(q2-q1,u2-u1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][q1+i][i6][i7][i8][u1+i][i10][i11];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1][i2][i3][i4][i5+1][i6][i7][i8][u1+i][i10][i11];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9+1][i10][i11];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1][i2][i3][i4][i5-1][i6][i7][i8][u2-i-1][i10][i11];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9-1][i10][i11];
                a[i1][i2][i3][i4][q1+i][i6][i7][i8][u1+i+1][i10][i11]=t;
            }
        }
    } else if(x==5&&y==10) {
        for(int i=0;i<min(q2-q1,v2-v1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][v1+i][i11];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1][i2][i3][i4][i5+1][i6][i7][i8][i9][v1+i][i11];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10+1][i11];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1][i2][i3][i4][i5-1][i6][i7][i8][i9][v2-i-1][i11];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10-1][i11];
                a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][v1+i+1][i11]=t;
            }
        }
    } else if(x==5&&y==11) {
        for(int i=0;i<min(q2-q1,w2-w1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) {
                ll t=a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][w1+i];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1][i2][i3][i4][i5+1][i6][i7][i8][i9][i10][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11+1];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1][i2][i3][i4][i5-1][i6][i7][i8][i9][i10][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11-1];
                a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][w1+i+1]=t;
            }
        }
    } else if(x==6&&y==1) {
        for(int i=0;i<min(r2-r1,m2-m1)/2;i++) {
            for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[m1+i][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2][i3][i4][i5][i6+1][i7][i8][i9][i10][i11];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1+1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2][i3][i4][i5][i6-1][i7][i8][i9][i10][i11];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1-1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11];
                a[m1+i+1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==6&&y==2) {
        for(int i=0;i<min(r2-r1,n2-n1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][n1+i][i3][i4][i5][r1+i][i7][i8][i9][i10][i11];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n1+i][i3][i4][i5][i6+1][i7][i8][i9][i10][i11];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1][i2+1][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n2-i-1][i3][i4][i5][i6-1][i7][i8][i9][i10][i11];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1][i2-1][i3][i4][i5][r1+i][i7][i8][i9][i10][i11];
                a[i1][n1+i+1][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==6&&y==3) {
        for(int i=0;i<min(r2-r1,o2-o1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][o1+i][i4][i5][r1+i][i7][i8][i9][i10][i11];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o1+i][i4][i5][i6+1][i7][i8][i9][i10][i11];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1][i2][i3+1][i4][i5][r2-i-1][i7][i8][i9][i10][i11];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o2-i-1][i4][i5][i6-1][i7][i8][i9][i10][i11];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1][i2][i3-1][i4][i5][r1+i][i7][i8][i9][i10][i11];
                a[i1][i2][o1+i+1][i4][i5][r1+i][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==6&&y==4) {
        for(int i=0;i<min(r2-r1,p2-p1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i5=q1;i5<q2;i5++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][p1+i][i5][r1+i][i7][i8][i9][i10][i11];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p1+i][i5][i6+1][i7][i8][i9][i10][i11];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4+1][i5][r2-i-1][i7][i8][i9][i10][i11];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p2-i-1][i5][i6-1][i7][i8][i9][i10][i11];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4-1][i5][r1+i][i7][i8][i9][i10][i11];
                a[i1][i2][i3][p1+i+1][i5][r1+i][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==6&&y==5) {
        for(int i=0;i<min(r2-r1,q2-q1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][q1+i][r1+i][i7][i8][i9][i10][i11];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q1+i][i6+1][i7][i8][i9][i10][i11];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5+1][r2-i-1][i7][i8][i9][i10][i11];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q2-i-1][i6-1][i7][i8][i9][i10][i11];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5-1][r1+i][i7][i8][i9][i10][i11];
                a[i1][i2][i3][i4][q1+i+1][r1+i][i7][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==6&&y==7) {
        for(int i=0;i<min(r2-r1,s2-s1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][r1+i][s1+i][i8][i9][i10][i11];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6+1][s1+i][i8][i9][i10][i11];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r2-i-1][i7+1][i8][i9][i10][i11];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6-1][s2-i-1][i8][i9][i10][i11];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r1+i][i7-1][i8][i9][i10][i11];
                a[i1][i2][i3][i4][i5][r1+i][s1+i+1][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==6&&y==8) {
        for(int i=0;i<min(r2-r1,t2-t1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i7=s1;i7<s2;i7++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][r1+i][i7][t1+i][i9][i10][i11];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6+1][i7][t1+i][i9][i10][i11];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r2-i-1][i7][i8+1][i9][i10][i11];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6-1][i7][t2-i-1][i9][i10][i11];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r1+i][i7][i8-1][i9][i10][i11];
                a[i1][i2][i3][i4][i5][r1+i][i7][t1+i+1][i9][i10][i11]=t;
            }
        }
    } else if(x==6&&y==9) {
        for(int i=0;i<min(r2-r1,u2-u1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][r1+i][i7][i8][u1+i][i10][i11];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1][i2][i3][i4][i5][i6+1][i7][i8][u1+i][i10][i11];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9+1][i10][i11];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1][i2][i3][i4][i5][i6-1][i7][i8][u2-i-1][i10][i11];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9-1][i10][i11];
                a[i1][i2][i3][i4][i5][r1+i][i7][i8][u1+i+1][i10][i11]=t;
            }
        }
    } else if(x==6&&y==10) {
        for(int i=0;i<min(r2-r1,v2-v1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][v1+i][i11];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1][i2][i3][i4][i5][i6+1][i7][i8][i9][v1+i][i11];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10+1][i11];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1][i2][i3][i4][i5][i6-1][i7][i8][i9][v2-i-1][i11];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10-1][i11];
                a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][v1+i+1][i11]=t;
            }
        }
    } else if(x==6&&y==11) {
        for(int i=0;i<min(r2-r1,w2-w1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) {
                ll t=a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][w1+i];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1][i2][i3][i4][i5][i6+1][i7][i8][i9][i10][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11+1];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1][i2][i3][i4][i5][i6-1][i7][i8][i9][i10][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11-1];
                a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][w1+i+1]=t;
            }
        }
    } else if(x==7&&y==1) {
        for(int i=0;i<min(s2-s1,m2-m1)/2;i++) {
            for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[m1+i][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2][i3][i4][i5][i6][i7+1][i8][i9][i10][i11];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1+1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2][i3][i4][i5][i6][i7-1][i8][i9][i10][i11];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1-1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11];
                a[m1+i+1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==7&&y==2) {
        for(int i=0;i<min(s2-s1,n2-n1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][n1+i][i3][i4][i5][i6][s1+i][i8][i9][i10][i11];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n1+i][i3][i4][i5][i6][i7+1][i8][i9][i10][i11];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1][i2+1][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n2-i-1][i3][i4][i5][i6][i7-1][i8][i9][i10][i11];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1][i2-1][i3][i4][i5][i6][s1+i][i8][i9][i10][i11];
                a[i1][n1+i+1][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==7&&y==3) {
        for(int i=0;i<min(s2-s1,o2-o1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][o1+i][i4][i5][i6][s1+i][i8][i9][i10][i11];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o1+i][i4][i5][i6][i7+1][i8][i9][i10][i11];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1][i2][i3+1][i4][i5][i6][s2-i-1][i8][i9][i10][i11];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o2-i-1][i4][i5][i6][i7-1][i8][i9][i10][i11];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1][i2][i3-1][i4][i5][i6][s1+i][i8][i9][i10][i11];
                a[i1][i2][o1+i+1][i4][i5][i6][s1+i][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==7&&y==4) {
        for(int i=0;i<min(s2-s1,p2-p1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][p1+i][i5][i6][s1+i][i8][i9][i10][i11];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p1+i][i5][i6][i7+1][i8][i9][i10][i11];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1][i2][i3][i4+1][i5][i6][s2-i-1][i8][i9][i10][i11];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p2-i-1][i5][i6][i7-1][i8][i9][i10][i11];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1][i2][i3][i4-1][i5][i6][s1+i][i8][i9][i10][i11];
                a[i1][i2][i3][p1+i+1][i5][i6][s1+i][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==7&&y==5) {
        for(int i=0;i<min(s2-s1,q2-q1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i6=r1;i6<r2;i6++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][q1+i][i6][s1+i][i8][i9][i10][i11];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q1+i][i6][i7+1][i8][i9][i10][i11];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5+1][i6][s2-i-1][i8][i9][i10][i11];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q2-i-1][i6][i7-1][i8][i9][i10][i11];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5-1][i6][s1+i][i8][i9][i10][i11];
                a[i1][i2][i3][i4][q1+i+1][i6][s1+i][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==7&&y==6) {
        for(int i=0;i<min(s2-s1,r2-r1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][r1+i][s1+i][i8][i9][i10][i11];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r1+i][i7+1][i8][i9][i10][i11];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6+1][s2-i-1][i8][i9][i10][i11];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r2-i-1][i7-1][i8][i9][i10][i11];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6-1][s1+i][i8][i9][i10][i11];
                a[i1][i2][i3][i4][i5][r1+i+1][s1+i][i8][i9][i10][i11]=t;
            }
        }
    } else if(x==7&&y==8) {
        for(int i=0;i<min(s2-s1,t2-t1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][i6][s1+i][t1+i][i9][i10][i11];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7+1][t1+i][i9][i10][i11];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][s2-i-1][i8+1][i9][i10][i11];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7-1][t2-i-1][i9][i10][i11];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][s1+i][i8-1][i9][i10][i11];
                a[i1][i2][i3][i4][i5][i6][s1+i][t1+i+1][i9][i10][i11]=t;
            }
        }
    } else if(x==7&&y==9) {
        for(int i=0;i<min(s2-s1,u2-u1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i8=t1;i8<t2;i8++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][i6][s1+i][i8][u1+i][i10][i11];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7+1][i8][u1+i][i10][i11];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9+1][i10][i11];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7-1][i8][u2-i-1][i10][i11];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9-1][i10][i11];
                a[i1][i2][i3][i4][i5][i6][s1+i][i8][u1+i+1][i10][i11]=t;
            }
        }
    } else if(x==7&&y==10) {
        for(int i=0;i<min(s2-s1,v2-v1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][v1+i][i11];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1][i2][i3][i4][i5][i6][i7+1][i8][i9][v1+i][i11];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10+1][i11];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1][i2][i3][i4][i5][i6][i7-1][i8][i9][v2-i-1][i11];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10-1][i11];
                a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][v1+i+1][i11]=t;
            }
        }
    } else if(x==7&&y==11) {
        for(int i=0;i<min(s2-s1,w2-w1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) {
                ll t=a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][w1+i];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1][i2][i3][i4][i5][i6][i7+1][i8][i9][i10][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11+1];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1][i2][i3][i4][i5][i6][i7-1][i8][i9][i10][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11-1];
                a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][w1+i+1]=t;
            }
        }
    } else if(x==8&&y==1) {
        for(int i=0;i<min(t2-t1,m2-m1)/2;i++) {
            for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[m1+i][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2][i3][i4][i5][i6][i7][i8+1][i9][i10][i11];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1+1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2][i3][i4][i5][i6][i7][i8-1][i9][i10][i11];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1-1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11];
                a[m1+i+1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=t;
            }
        }
    } else if(x==8&&y==2) {
        for(int i=0;i<min(t2-t1,n2-n1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][n1+i][i3][i4][i5][i6][i7][t1+i][i9][i10][i11];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n1+i][i3][i4][i5][i6][i7][i8+1][i9][i10][i11];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1][i2+1][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n2-i-1][i3][i4][i5][i6][i7][i8-1][i9][i10][i11];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1][i2-1][i3][i4][i5][i6][i7][t1+i][i9][i10][i11];
                a[i1][n1+i+1][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=t;
            }
        }
    } else if(x==8&&y==3) {
        for(int i=0;i<min(t2-t1,o2-o1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][o1+i][i4][i5][i6][i7][t1+i][i9][i10][i11];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o1+i][i4][i5][i6][i7][i8+1][i9][i10][i11];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1][i2][i3+1][i4][i5][i6][i7][t2-i-1][i9][i10][i11];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o2-i-1][i4][i5][i6][i7][i8-1][i9][i10][i11];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1][i2][i3-1][i4][i5][i6][i7][t1+i][i9][i10][i11];
                a[i1][i2][o1+i+1][i4][i5][i6][i7][t1+i][i9][i10][i11]=t;
            }
        }
    } else if(x==8&&y==4) {
        for(int i=0;i<min(t2-t1,p2-p1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][p1+i][i5][i6][i7][t1+i][i9][i10][i11];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p1+i][i5][i6][i7][i8+1][i9][i10][i11];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1][i2][i3][i4+1][i5][i6][i7][t2-i-1][i9][i10][i11];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p2-i-1][i5][i6][i7][i8-1][i9][i10][i11];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1][i2][i3][i4-1][i5][i6][i7][t1+i][i9][i10][i11];
                a[i1][i2][i3][p1+i+1][i5][i6][i7][t1+i][i9][i10][i11]=t;
            }
        }
    } else if(x==8&&y==5) {
        for(int i=0;i<min(t2-t1,q2-q1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][q1+i][i6][i7][t1+i][i9][i10][i11];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q1+i][i6][i7][i8+1][i9][i10][i11];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1][i2][i3][i4][i5+1][i6][i7][t2-i-1][i9][i10][i11];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q2-i-1][i6][i7][i8-1][i9][i10][i11];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1][i2][i3][i4][i5-1][i6][i7][t1+i][i9][i10][i11];
                a[i1][i2][i3][i4][q1+i+1][i6][i7][t1+i][i9][i10][i11]=t;
            }
        }
    } else if(x==8&&y==6) {
        for(int i=0;i<min(t2-t1,r2-r1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i7=s1;i7<s2;i7++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][r1+i][i7][t1+i][i9][i10][i11];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r1+i][i7][i8+1][i9][i10][i11];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6+1][i7][t2-i-1][i9][i10][i11];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r2-i-1][i7][i8-1][i9][i10][i11];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6-1][i7][t1+i][i9][i10][i11];
                a[i1][i2][i3][i4][i5][r1+i+1][i7][t1+i][i9][i10][i11]=t;
            }
        }
    } else if(x==8&&y==7) {
        for(int i=0;i<min(t2-t1,s2-s1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][i6][s1+i][t1+i][i9][i10][i11];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][s1+i][i8+1][i9][i10][i11];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7+1][t2-i-1][i9][i10][i11];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][s2-i-1][i8-1][i9][i10][i11];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7-1][t1+i][i9][i10][i11];
                a[i1][i2][i3][i4][i5][i6][s1+i+1][t1+i][i9][i10][i11]=t;
            }
        }
    } else if(x==8&&y==9) {
        for(int i=0;i<min(t2-t1,u2-u1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][i6][i7][t1+i][u1+i][i10][i11];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8+1][u1+i][i10][i11];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9+1][i10][i11];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8-1][u2-i-1][i10][i11];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9-1][i10][i11];
                a[i1][i2][i3][i4][i5][i6][i7][t1+i][u1+i+1][i10][i11]=t;
            }
        }
    } else if(x==8&&y==10) {
        for(int i=0;i<min(t2-t1,v2-v1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i9=u1;i9<u2;i9++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][v1+i][i11];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8+1][i9][v1+i][i11];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10+1][i11];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8-1][i9][v2-i-1][i11];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10-1][i11];
                a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][v1+i+1][i11]=t;
            }
        }
    } else if(x==8&&y==11) {
        for(int i=0;i<min(t2-t1,w2-w1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) {
                ll t=a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][w1+i];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1][i2][i3][i4][i5][i6][i7][i8+1][i9][i10][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11+1];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1][i2][i3][i4][i5][i6][i7][i8-1][i9][i10][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11-1];
                a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][w1+i+1]=t;
            }
        }
    } else if(x==9&&y==1) {
        for(int i=0;i<min(u2-u1,m2-m1)/2;i++) {
            for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[m1+i][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9+1][i10][i11];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1+1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9-1][i10][i11];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1-1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11];
                a[m1+i+1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=t;
            }
        }
    } else if(x==9&&y==2) {
        for(int i=0;i<min(u2-u1,n2-n1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][n1+i][i3][i4][i5][i6][i7][i8][u1+i][i10][i11];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9+1][i10][i11];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1][i2+1][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9-1][i10][i11];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1][i2-1][i3][i4][i5][i6][i7][i8][u1+i][i10][i11];
                a[i1][n1+i+1][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=t;
            }
        }
    } else if(x==9&&y==3) {
        for(int i=0;i<min(u2-u1,o2-o1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][o1+i][i4][i5][i6][i7][i8][u1+i][i10][i11];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9+1][i10][i11];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1][i2][i3+1][i4][i5][i6][i7][i8][u2-i-1][i10][i11];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9-1][i10][i11];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1][i2][i3-1][i4][i5][i6][i7][i8][u1+i][i10][i11];
                a[i1][i2][o1+i+1][i4][i5][i6][i7][i8][u1+i][i10][i11]=t;
            }
        }
    } else if(x==9&&y==4) {
        for(int i=0;i<min(u2-u1,p2-p1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][p1+i][i5][i6][i7][i8][u1+i][i10][i11];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9+1][i10][i11];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1][i2][i3][i4+1][i5][i6][i7][i8][u2-i-1][i10][i11];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9-1][i10][i11];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1][i2][i3][i4-1][i5][i6][i7][i8][u1+i][i10][i11];
                a[i1][i2][i3][p1+i+1][i5][i6][i7][i8][u1+i][i10][i11]=t;
            }
        }
    } else if(x==9&&y==5) {
        for(int i=0;i<min(u2-u1,q2-q1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][q1+i][i6][i7][i8][u1+i][i10][i11];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9+1][i10][i11];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1][i2][i3][i4][i5+1][i6][i7][i8][u2-i-1][i10][i11];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9-1][i10][i11];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1][i2][i3][i4][i5-1][i6][i7][i8][u1+i][i10][i11];
                a[i1][i2][i3][i4][q1+i+1][i6][i7][i8][u1+i][i10][i11]=t;
            }
        }
    } else if(x==9&&y==6) {
        for(int i=0;i<min(u2-u1,r2-r1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][r1+i][i7][i8][u1+i][i10][i11];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9+1][i10][i11];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1][i2][i3][i4][i5][i6+1][i7][i8][u2-i-1][i10][i11];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9-1][i10][i11];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1][i2][i3][i4][i5][i6-1][i7][i8][u1+i][i10][i11];
                a[i1][i2][i3][i4][i5][r1+i+1][i7][i8][u1+i][i10][i11]=t;
            }
        }
    } else if(x==9&&y==7) {
        for(int i=0;i<min(u2-u1,s2-s1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i8=t1;i8<t2;i8++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][i6][s1+i][i8][u1+i][i10][i11];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9+1][i10][i11];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7+1][i8][u2-i-1][i10][i11];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9-1][i10][i11];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7-1][i8][u1+i][i10][i11];
                a[i1][i2][i3][i4][i5][i6][s1+i+1][i8][u1+i][i10][i11]=t;
            }
        }
    } else if(x==9&&y==8) {
        for(int i=0;i<min(u2-u1,t2-t1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i10=v1;i10<v2;i10++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][i6][i7][t1+i][u1+i][i10][i11];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9+1][i10][i11];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8+1][u2-i-1][i10][i11];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9-1][i10][i11];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8-1][u1+i][i10][i11];
                a[i1][i2][i3][i4][i5][i6][i7][t1+i+1][u1+i][i10][i11]=t;
            }
        }
    } else if(x==9&&y==10) {
        for(int i=0;i<min(u2-u1,v2-v1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][v1+i][i11];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8][i9+1][v1+i][i11];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10+1][i11];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8][i9-1][v2-i-1][i11];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10-1][i11];
                a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][v1+i+1][i11]=t;
            }
        }
    } else if(x==9&&y==11) {
        for(int i=0;i<min(u2-u1,w2-w1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i10=v1;i10<v2;i10++) {
                ll t=a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][w1+i];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1][i2][i3][i4][i5][i6][i7][i8][i9+1][i10][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11+1];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1][i2][i3][i4][i5][i6][i7][i8][i9-1][i10][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11-1];
                a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][w1+i+1]=t;
            }
        }
    } else if(x==10&&y==1) {
        for(int i=0;i<min(v2-v1,m2-m1)/2;i++) {
            for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10+1][i11];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1+1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10-1][i11];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1-1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11];
                a[m1+i+1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=t;
            }
        }
    } else if(x==10&&y==2) {
        for(int i=0;i<min(v2-v1,n2-n1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][v1+i][i11];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10+1][i11];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1][i2+1][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10-1][i11];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1][i2-1][i3][i4][i5][i6][i7][i8][i9][v1+i][i11];
                a[i1][n1+i+1][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=t;
            }
        }
    } else if(x==10&&y==3) {
        for(int i=0;i<min(v2-v1,o2-o1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][v1+i][i11];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10+1][i11];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1][i2][i3+1][i4][i5][i6][i7][i8][i9][v2-i-1][i11];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10-1][i11];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1][i2][i3-1][i4][i5][i6][i7][i8][i9][v1+i][i11];
                a[i1][i2][o1+i+1][i4][i5][i6][i7][i8][i9][v1+i][i11]=t;
            }
        }
    } else if(x==10&&y==4) {
        for(int i=0;i<min(v2-v1,p2-p1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][v1+i][i11];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10+1][i11];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1][i2][i3][i4+1][i5][i6][i7][i8][i9][v2-i-1][i11];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10-1][i11];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1][i2][i3][i4-1][i5][i6][i7][i8][i9][v1+i][i11];
                a[i1][i2][i3][p1+i+1][i5][i6][i7][i8][i9][v1+i][i11]=t;
            }
        }
    } else if(x==10&&y==5) {
        for(int i=0;i<min(v2-v1,q2-q1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][v1+i][i11];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10+1][i11];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1][i2][i3][i4][i5+1][i6][i7][i8][i9][v2-i-1][i11];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10-1][i11];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1][i2][i3][i4][i5-1][i6][i7][i8][i9][v1+i][i11];
                a[i1][i2][i3][i4][q1+i+1][i6][i7][i8][i9][v1+i][i11]=t;
            }
        }
    } else if(x==10&&y==6) {
        for(int i=0;i<min(v2-v1,r2-r1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][v1+i][i11];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10+1][i11];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1][i2][i3][i4][i5][i6+1][i7][i8][i9][v2-i-1][i11];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10-1][i11];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1][i2][i3][i4][i5][i6-1][i7][i8][i9][v1+i][i11];
                a[i1][i2][i3][i4][i5][r1+i+1][i7][i8][i9][v1+i][i11]=t;
            }
        }
    } else if(x==10&&y==7) {
        for(int i=0;i<min(v2-v1,s2-s1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][v1+i][i11];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10+1][i11];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1][i2][i3][i4][i5][i6][i7+1][i8][i9][v2-i-1][i11];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10-1][i11];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1][i2][i3][i4][i5][i6][i7-1][i8][i9][v1+i][i11];
                a[i1][i2][i3][i4][i5][i6][s1+i+1][i8][i9][v1+i][i11]=t;
            }
        }
    } else if(x==10&&y==8) {
        for(int i=0;i<min(v2-v1,t2-t1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i9=u1;i9<u2;i9++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][v1+i][i11];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10+1][i11];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8+1][i9][v2-i-1][i11];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10-1][i11];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8-1][i9][v1+i][i11];
                a[i1][i2][i3][i4][i5][i6][i7][t1+i+1][i9][v1+i][i11]=t;
            }
        }
    } else if(x==10&&y==9) {
        for(int i=0;i<min(v2-v1,u2-u1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i11=w1;i11<w2;i11++) {
                ll t=a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][v1+i][i11];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10+1][i11];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8][i9+1][v2-i-1][i11];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10-1][i11];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8][i9-1][v1+i][i11];
                a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i+1][v1+i][i11]=t;
            }
        }
    } else if(x==10&&y==11) {
        for(int i=0;i<min(v2-v1,w2-w1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) {
                ll t=a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][w1+i];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10+1][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11+1];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10-1][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11-1];
                a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][w1+i+1]=t;
            }
        }
    } else if(x==11&&y==1) {
        for(int i=0;i<min(w2-w1,m2-m1)/2;i++) {
            for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) {
                ll t=a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m1+i][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11+1];
                for(int i1=m1+i;i1<m2-i-1;i1++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1+1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[m2-i-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11-1];
                for(int i1=m2-i-1;i1>m1+i;i1--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1-1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i];
                a[m1+i+1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=t;
            }
        }
    } else if(x==11&&y==2) {
        for(int i=0;i<min(w2-w1,n2-n1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) {
                ll t=a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n1+i][i3][i4][i5][i6][i7][i8][i9][i10][i11+1];
                for(int i2=n1+i;i2<n2-i-1;i2++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1][i2+1][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][n2-i-1][i3][i4][i5][i6][i7][i8][i9][i10][i11-1];
                for(int i2=n2-i-1;i2>n1+i;i2--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1][i2-1][i3][i4][i5][i6][i7][i8][i9][i10][w1+i];
                a[i1][n1+i+1][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=t;
            }
        }
    } else if(x==11&&y==3) {
        for(int i=0;i<min(w2-w1,o2-o1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) {
                ll t=a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o1+i][i4][i5][i6][i7][i8][i9][i10][i11+1];
                for(int i3=o1+i;i3<o2-i-1;i3++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1][i2][i3+1][i4][i5][i6][i7][i8][i9][i10][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][o2-i-1][i4][i5][i6][i7][i8][i9][i10][i11-1];
                for(int i3=o2-i-1;i3>o1+i;i3--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1][i2][i3-1][i4][i5][i6][i7][i8][i9][i10][w1+i];
                a[i1][i2][o1+i+1][i4][i5][i6][i7][i8][i9][i10][w1+i]=t;
            }
        }
    } else if(x==11&&y==4) {
        for(int i=0;i<min(w2-w1,p2-p1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) {
                ll t=a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p1+i][i5][i6][i7][i8][i9][i10][i11+1];
                for(int i4=p1+i;i4<p2-i-1;i4++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1][i2][i3][i4+1][i5][i6][i7][i8][i9][i10][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][p2-i-1][i5][i6][i7][i8][i9][i10][i11-1];
                for(int i4=p2-i-1;i4>p1+i;i4--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1][i2][i3][i4-1][i5][i6][i7][i8][i9][i10][w1+i];
                a[i1][i2][i3][p1+i+1][i5][i6][i7][i8][i9][i10][w1+i]=t;
            }
        }
    } else if(x==11&&y==5) {
        for(int i=0;i<min(w2-w1,q2-q1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) {
                ll t=a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q1+i][i6][i7][i8][i9][i10][i11+1];
                for(int i5=q1+i;i5<q2-i-1;i5++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1][i2][i3][i4][i5+1][i6][i7][i8][i9][i10][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][q2-i-1][i6][i7][i8][i9][i10][i11-1];
                for(int i5=q2-i-1;i5>q1+i;i5--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1][i2][i3][i4][i5-1][i6][i7][i8][i9][i10][w1+i];
                a[i1][i2][i3][i4][q1+i+1][i6][i7][i8][i9][i10][w1+i]=t;
            }
        }
    } else if(x==11&&y==6) {
        for(int i=0;i<min(w2-w1,r2-r1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) {
                ll t=a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r1+i][i7][i8][i9][i10][i11+1];
                for(int i6=r1+i;i6<r2-i-1;i6++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1][i2][i3][i4][i5][i6+1][i7][i8][i9][i10][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][r2-i-1][i7][i8][i9][i10][i11-1];
                for(int i6=r2-i-1;i6>r1+i;i6--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1][i2][i3][i4][i5][i6-1][i7][i8][i9][i10][w1+i];
                a[i1][i2][i3][i4][i5][r1+i+1][i7][i8][i9][i10][w1+i]=t;
            }
        }
    } else if(x==11&&y==7) {
        for(int i=0;i<min(w2-w1,s2-s1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) {
                ll t=a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][s1+i][i8][i9][i10][i11+1];
                for(int i7=s1+i;i7<s2-i-1;i7++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1][i2][i3][i4][i5][i6][i7+1][i8][i9][i10][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][s2-i-1][i8][i9][i10][i11-1];
                for(int i7=s2-i-1;i7>s1+i;i7--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1][i2][i3][i4][i5][i6][i7-1][i8][i9][i10][w1+i];
                a[i1][i2][i3][i4][i5][i6][s1+i+1][i8][i9][i10][w1+i]=t;
            }
        }
    } else if(x==11&&y==8) {
        for(int i=0;i<min(w2-w1,t2-t1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i9=u1;i9<u2;i9++) for(int i10=v1;i10<v2;i10++) {
                ll t=a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][t1+i][i9][i10][i11+1];
                for(int i8=t1+i;i8<t2-i-1;i8++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1][i2][i3][i4][i5][i6][i7][i8+1][i9][i10][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][t2-i-1][i9][i10][i11-1];
                for(int i8=t2-i-1;i8>t1+i;i8--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1][i2][i3][i4][i5][i6][i7][i8-1][i9][i10][w1+i];
                a[i1][i2][i3][i4][i5][i6][i7][t1+i+1][i9][i10][w1+i]=t;
            }
        }
    } else if(x==11&&y==9) {
        for(int i=0;i<min(w2-w1,u2-u1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i10=v1;i10<v2;i10++) {
                ll t=a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i][i10][i11+1];
                for(int i9=u1+i;i9<u2-i-1;i9++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1][i2][i3][i4][i5][i6][i7][i8][i9+1][i10][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8][u2-i-1][i10][i11-1];
                for(int i9=u2-i-1;i9>u1+i;i9--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1][i2][i3][i4][i5][i6][i7][i8][i9-1][i10][w1+i];
                a[i1][i2][i3][i4][i5][i6][i7][i8][u1+i+1][i10][w1+i]=t;
            }
        }
    } else if(x==11&&y==10) {
        for(int i=0;i<min(w2-w1,v2-v1)/2;i++) {
            for(int i1=m1;i1<m2;i1++) for(int i2=n1;i2<n2;i2++) for(int i3=o1;i3<o2;i3++) for(int i4=p1;i4<p2;i4++) for(int i5=q1;i5<q2;i5++) for(int i6=r1;i6<r2;i6++) for(int i7=s1;i7<s2;i7++) for(int i8=t1;i8<t2;i8++) for(int i9=u1;i9<u2;i9++) {
                ll t=a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][w1+i];
                for(int i11=w1+i;i11<w2-i-1;i11++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i][i11+1];
                for(int i10=v1+i;i10<v2-i-1;i10++) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w2-i-1]=a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10+1][w2-i-1];
                for(int i11=w2-i-1;i11>w1+i;i11--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11]=a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v2-i-1][i11-1];
                for(int i10=v2-i-1;i10>v1+i;i10--) a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][w1+i]=a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10-1][w1+i];
                a[i1][i2][i3][i4][i5][i6][i7][i8][i9][v1+i+1][w1+i]=t;
            }
        }
    }
}
void q3(int op) {
    if(op==67)swap(d[0],d[1]);else if(op==68)swap(d[0],d[2]);else if(op==69)swap(d[0],d[3]);else if(op==70)swap(d[0],d[4]);else if(op==71)swap(d[0],d[5]);else if(op==72)swap(d[0],d[6]);else if(op==73)swap(d[0],d[7]);else if(op==74)swap(d[0],d[8]);else if(op==75)swap(d[0],d[9]);else if(op==76)swap(d[0],d[10]);else if(op==77)swap(d[1],d[2]);else if(op==78)swap(d[1],d[3]);else if(op==79)swap(d[1],d[4]);else if(op==80)swap(d[1],d[5]);else if(op==81)swap(d[1],d[6]);else if(op==82)swap(d[1],d[7]);else if(op==83)swap(d[1],d[8]);else if(op==84)swap(d[1],d[9]);else if(op==85)swap(d[1],d[10]);else if(op==86)swap(d[2],d[3]);else if(op==87)swap(d[2],d[4]);else if(op==88)swap(d[2],d[5]);else if(op==89)swap(d[2],d[6]);else if(op==90)swap(d[2],d[7]);else if(op==91)swap(d[2],d[8]);else if(op==92)swap(d[2],d[9]);else if(op==93)swap(d[2],d[10]);else if(op==94)swap(d[3],d[4]);else if(op==95)swap(d[3],d[5]);else if(op==96)swap(d[3],d[6]);else if(op==97)swap(d[3],d[7]);else if(op==98)swap(d[3],d[8]);else if(op==99)swap(d[3],d[9]);else if(op==100)swap(d[3],d[10]);else if(op==101)swap(d[4],d[5]);else if(op==102)swap(d[4],d[6]);else if(op==103)swap(d[4],d[7]);else if(op==104)swap(d[4],d[8]);else if(op==105)swap(d[4],d[9]);else if(op==106)swap(d[4],d[10]);else if(op==107)swap(d[5],d[6]);else if(op==108)swap(d[5],d[7]);else if(op==109)swap(d[5],d[8]);else if(op==110)swap(d[5],d[9]);else if(op==111)swap(d[5],d[10]);else if(op==112)swap(d[6],d[7]);else if(op==113)swap(d[6],d[8]);else if(op==114)swap(d[6],d[9]);else if(op==115)swap(d[6],d[10]);else if(op==116)swap(d[7],d[8]);else if(op==117)swap(d[7],d[9]);else if(op==118)swap(d[7],d[10]);else if(op==119)swap(d[8],d[9]);else if(op==120)swap(d[8],d[10]);else swap(d[9],d[10]);
}
int main() {
    int m,n,o,p,q,r,s,t,u,v,w,rho,op;
    cin>>m>>n>>o>>p>>q>>r>>s>>t>>u>>v>>w;
    vector<vector<vector<vector<vector<vector<vector<vector<vector<vector<vector<ll>>>>>>>>>>> a(m,vector<vector<vector<vector<vector<vector<vector<vector<vector<vector<ll>>>>>>>>>>(n,vector<vector<vector<vector<vector<vector<vector<vector<vector<ll>>>>>>>>>(o,vector<vector<vector<vector<vector<vector<vector<vector<ll>>>>>>>>(p,vector<vector<vector<vector<vector<vector<vector<ll>>>>>>>(q,vector<vector<vector<vector<vector<vector<ll>>>>>>(r,vector<vector<vector<vector<vector<ll>>>>>(s,vector<vector<vector<vector<ll>>>>(t,vector<vector<vector<ll>>>(u,vector<vector<ll>>(v,vector<ll>(w)))))))))));
    for(int i1=0;i1<m;i1++) for(int i2=0;i2<n;i2++) for(int i3=0;i3<o;i3++) for(int i4=0;i4<p;i4++) for(int i5=0;i5<q;i5++) for(int i6=0;i6<r;i6++) for(int i7=0;i7<s;i7++) for(int i8=0;i8<t;i8++) for(int i9=0;i9<u;i9++) for(int i10=0;i10<v;i10++) for(int i11=0;i11<w;i11++) cin>>a[i1][i2][i3][i4][i5][i6][i7][i8][i9][i10][i11];
    cin>>rho;
    while(rho--) {
        cin>>op;
        if(op<12) q1(a,op);
        else if(op<67) q2(a,op);
        else q3(op);
    } vector<int> axis={m,n,o,p,q,r,s,t,u,v,w};
    for(int i=0;i<11;i++) cout<<axis[d[i]-1]<<' ';
    cout<<'\n';
    for(int i1=0;i1<axis[d[0]-1];i1++) {
    for(int i2=0;i2<axis[d[1]-1];i2++) {
    for(int i3=0;i3<axis[d[2]-1];i3++) {
    for(int i4=0;i4<axis[d[3]-1];i4++) {
    for(int i5=0;i5<axis[d[4]-1];i5++) {
    for(int i6=0;i6<axis[d[5]-1];i6++) {
    for(int i7=0;i7<axis[d[6]-1];i7++) {
    for(int i8=0;i8<axis[d[7]-1];i8++) {
    for(int i9=0;i9<axis[d[8]-1];i9++) {
    for(int i10=0;i10<axis[d[9]-1];i10++) {
    for(int i11=0;i11<axis[d[10]-1];i11++) {
        vector<int> v={i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11};
        vector<int> r(11);
        for(int i=0;i<11;i++) r[d[i]-1]=v[i];
        cout<<a[r[0]][r[1]][r[2]][r[3]][r[4]][r[5]][r[6]][r[7]][r[8]][r[9]][r[10]]<<' ';
    } cout<<'\n';}}}}}}}}}}
}
