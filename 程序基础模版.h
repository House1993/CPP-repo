//#pragma comment(linker, "/STACK:102400000,102400000")
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include<queue>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;
typedef long long LL;
//splay treap
//#define keytree ch[ch[root][1]][0]
//#define L(x) (ch[x][0])
//#define R(x) (ch[x][1])
//segtree
//#define L(x) (x<<1)
//#define R(x) ((x<<1)|1)
//#define MID(x,y) ((x+y)>>1)
//#define lowbit(x) (x&(-x))
#define inf ((1U<<31)-1)
#define N 100010

//输入加速
template<class T> //适合正整数
inline void scan_d(T &ret) {
	char c;
	ret = 0;
	while ((c = getchar()) < '0' || c > '9')
		;
	while (c >= '0' && c <= '9')
		ret = ret * 10 + (c - '0'), c = getchar();
}

template<class T> //适合正负整数
inline bool scan_d(T &ret) {
	char c;
	int sgn;
	if (c = getchar(), c == EOF)
		return 0; //EOF
	while (c != '-' && (c < '0' || c > '9'))
		c = getchar();
	sgn = (c == '-') ? -1 : 1;
	ret = (c == '-') ? 0 : (c - '0');
	while (c = getchar(), c >= '0' && c <= '9')
		ret = ret * 10 + (c - '0');
	ret *= sgn;
	return 1;
}

template<class T> //适合浮点数
inline bool scan_d(T &ret) {
	char c;
	int sgn;
	T bit = 0.1;
	if (c = getchar(), c == EOF)
		return 0;
	while (c != '-' && c != '.' && (c < '0' || c > '9'))
		c = getchar();
	sgn = (c == '-') ? -1 : 1;
	ret = (c == '-') ? 0 : (c - '0');
	while (c = getchar(), c >= '0' && c <= '9')
		ret = ret * 10 + (c - '0');
	if (c == ' ' || c == '\n') {
		ret *= sgn;
		return 1;
	}
	while (c = getchar(), c >= '0' && c <= '9')
		ret += (c - '0') * bit, bit /= 10;
	ret *= sgn;
	return 1;
}

//输出加速  适合正整数  负数要特判符号  注意x类型
inline void out(int x) {
	if (x > 9)
		out(x / 10);
	putchar(x % 10 + '0');
}

int main() {
	ios::sync_with_stdio(false);
	return 0;
}
