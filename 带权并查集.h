//带权并查集
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#define M 20005
using namespace std;
struct node{
	int x,y,v;
}s[M*10];
int father[M];
int offset[M];
int get(int v){
	if(father[v]!=v){
		int t=father[v];
		father[v]=get(father[v]);
		offset[v]=(offset[v]+offset[t])%2;			
	}
	return father[v];
}
bool cmp(node a,node b){
	return a.v>b.v;
};
int main(){
	int n,m,i,j;
	while(scanf("%d %d",&n,&m)!=EOF){
		for(i=1;i<=n;i++){
			father[i]=i;
			offset[i]=0;
		}
		for(i=0;i<m;i++)
			scanf("%d %d %d",&s[i].x,&s[i].y,&s[i].v);
		sort(s,s+m,cmp);
		s[m].v=0;
		for(i=0;i<m;i++){
			int x=s[i].x;
			int y=s[i].y;
			int fx=get(x);
			int fy=get(y);
			if(fx!=fy){
				father[fx]=fy;
				offset[fx]=(1-offset[x]+offset[y]+2)%2;
			}else{
				if((offset[x]-offset[y]+2)%2!=1)
					break;
			}
		}
		printf("%d\n",s[i].v);
	}
	return 0;
}