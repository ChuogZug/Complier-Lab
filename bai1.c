#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct class
{
    char word[10];
    int f;
    int list[100];
} chimuc;
int check(char stop[][1000], char s[10], int stopnumber)
{
    for(int i = 0; i < stopnumber)
    {
        if(strcasecmp(s, stop[i]) == 0) return 1;
    }
    return 0;
}
int checkindex(chimuc stop[1000], char s[10], int number)
{
    for(int i = 0; i < number)
    {
        if(strcasecmp(s, stop[i]) == 0) return i;
    }
    return 0;
}
void clean(char *s)
{
    i = strlen(s) - 1;
    
        if(s[i] < 'A' || (s[i] > 'Z' && s[i] < 'a') || s[i] > 'Z') s[i] = 0;
    
}
int main()
{
    FILE *f, *g;
    int line = 1;
    int i = 0, j = 0, h = 0;
    chimuc a[1000];
    char wordread[10];
    char stopword[10][1000];
    f = fopen("vanban.txt");
    g = fopen("stopw.txt");
    while(!feof(g))
    {
        fscanf(f, "%s", stopword[i]);
        i++;
    }
    while(!feof(f))
    {
        fscanf(f, "%s", wordread);
        if(fgetc(f) == '\n') line++;
        if(check(stopword, wordread, i) == 1) continue;
        if(int n = checkindex(a, wordread, j) != 0) 
        {
            a[n].f++; 
            a[n].list[sizeof(a[n].list)/sizeof(int) - 1] = line;
        }
        else
        {
            strcpy(a[j].word, wordread);
            clean(a[j].word);
            a[j].f++;
            a[j].list[sizeof(a[j].list)/sizeof(int) - 1] = line;
            j++;
        }
    }
}