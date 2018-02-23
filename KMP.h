//KMP算法求最小循环节，这里有一个结论，最小循环节的大小为len-next[len]。
//最小循环节只有在 len % (len-next[len]) == 0 时才存在
//KMP求出的next[i]可以表示出0~i-1区间的前缀和后缀相同的字符数为next[i]
#include<stdio.h>
#include<string.h>
#define M 1000
char st1[M];//主串
char st2[M];//模式串
int next[M];

void GetNext(char st2[]){
	int len = strlen(st2);
	int i = 0,j = -1;
	next[0] = -1;
	while(i < len){
		if(j == -1||st2[i] == st2[j]){
			i++;
			j++;
			next[i] = j;
		}else{
			j = next[j];
		}
	}
}

int KMP(char st1[],char st2[]){
	int len1 = strlen(st1);
	int len2 = strlen(st2);
	int i = 0, j = 0;
	while(i < len1&&j < len2){
		if(j == -1||st1[i] == st2[j]){
			i++;
			j++;
		}else{
			j = next[j];
		}
	}
	if(j == len2){
		return i - len2;
	}
	return -1;
}
//next版本2
void GetNext(char st2[]){
	int len = strlen(st2);
	int i = 0,j = -1;
	next[0] = -1;
	while (i<len)
	{
		while (j>=0 && st2[i]!=st2[j]) j=next[j];
		i++;
		j++;
		next[i]=j;
	}
}

int KMP(char st1[],char st2[]){
	int len1 = strlen(st1);
	int len2 = strlen(st2);
	int i = 0, j = 0;
	while (i<len1)
	{
		while (j>=0 && st1[i]!=st2[j]) j=next[j];
		i++;
		j++;
		if (j==len2)
			return i-len2;
	}
	return -1;
}

//nextval版本
void get_nextval(char const* ptrn, int plen, int* nextval) 
{ 
	int i = 0; 
	nextval[i] = -1; 
	int j = -1; 
	while( i < plen ) 
	{ 
		if( j == -1 || ptrn[i] == ptrn[j] )
		{ 
			++i; 
			++j; 
			if( ptrn[i] != ptrn[j] ) nextval[i] = j;//++i，++j之后，再次判断ptrn[i]与ptrn[j]的关系
			else nextval[i] = nextval[j]; 
		} 
		else j = nextval[j]; 
	} 
} 

int kmp_search(char const* src, int slen, char const* patn, int plen, int const* nextval, int pos) //此代码支持从pos位开始匹配
{
	int i = pos; 
	int j = 0; 
	while ( i < slen && j < plen ) 
	{ 
		if( j == -1 || src[i] == patn[j] ) 
		{ 
			++i; 
			++j; 
		} 
		else j = nextval[j]; //当匹配失败的时候直接用p[j_next]与s[i]比较，即匹配失效后下一次匹配的位置 
	} 
	if( j >= plen ) return i-plen; 
	else return -1; 
} 
