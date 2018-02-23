/*
有两个字符串，用S匹配T，即查看T中有没有S的某个后缀。
扩展kmp有一个ext[i]数组，表示S[i]与T匹配的最长公共前缀的长度。
思想就是利用kmp的方法，不进行重复比较，增加时间效率。
利用nxt[]数组，nxt[i]表示T[i..m]与T的最长公共前缀长度。
i+nxt[i]的长度就是重复子串（带循环节的串）的长度
处理的时间复杂度O(n)
*/

#define M 1020
int nxt[M], ext[M];

void ExtendKmp(char s[], int ls, char t[], int lt) {
    int i, j, k;
    int Len, L;
    j = 0;
    while (t[j + 1] == t[j] && j + 1 < lt) j++;
    nxt[1] = j, k = 1;
    for (i = 2; i < lt; i++) {
        Len = k + nxt[k], L = nxt[i - k];
        if (Len > L + i) nxt[i] = L;
        else {
            j = Len - i > 0 ? Len - i : 0;
            while (t[i + j] == t[j] && i + j < lt) j++;
            nxt[i] = j, k = i;
        }
    }
    j = 0;
    while (s[j] == t[j] && j < lt && j < ls) j++;
    ext[0] = j, k = 0;
    for (i = 1; i < ls; i++) {
        Len = k + ext[k], L = nxt[i - k];
        if (Len > L + i) ext[i] = L;
        else {
            j = Len - i > 0 ? Len - i : 0;
            while (s[i + j] == t[j] && i + j < ls && j < lt) j++;
            ext[i] = j, k = i;
        }
    }
}
