#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
typedef struct class
{
    char word[20];
    int f;
    int list[100];
} chimuc;
int check(char stop[][1000], char *s, int stopnumber)
{
    for(int i = 0; i < stopnumber; i++)
    {
        if(strcasecmp(s, stop[i]) == 0) return 1;
    }
    return 0;
}
int checkindex(chimuc stop[1000], char *s, int number)
{
    for(int i = 0; i < number; i++)
    {
        if(strcasecmp(s, stop[i].word) == 0) return i;
    }
    return 0;
}
int count(int *list)
{
    for(int i = 0; i < 1000; i++)
    {
        if(list[i] == 0) return i;
    }
}
int Allupper(char *s)
{
    for(int i = 0; i < strlen(s); i++) if(islower(s[i])) return 0;
    return 1;
}
int main()
{
    FILE *f, *g;
    chimuc w[1000];
    chimuc cleanword[1000];
    char read[400];
    char stopword[10][1000];
    int i = 0, line = 0, k = 0, h = 0, j, l = 0;
    f = fopen("vanban.txt", "r");
    g = fopen("stopw.txt", "r");
    while(!feof(g))
    {
        fscanf(g, "%s", stopword[i]);
        i++;
    }
    int stopnum = i;
    fclose(g);
    while(!feof(f))
    {
        j = 0;
        fgets(read, 4000, f);
        line++;
        while(j < strlen(read))
        {
            while(isalpha(read[j]))
            {
                w[k].word[h++] = read[j++]; 
            }
            if(h){
            w[k].list[0] = line;
            w[k].word[h] = 0;
            h = 0;
            k++;
            }
            if(read[j] == '.')
            {
                for(int i = l+1; i < k; i++)
                {
                    if(isupper(w[i].word[0])) strcpy(w[i].word, "DTR"); 
                }
                l = k;
            }
            j++;
        }
    }
    fclose(f);
        for(int i = 0; i < k; i++)
        {
            if(Allupper(w[i].word)) strcpy(w[i].word, "DTR"); 
        }
    for(int i = 0; i < k; i++)
    {
        if(strcmp(w[i].word, "DTR") != 0) for(int j = 0; j < strlen(w[i].word); j++) w[i].word[j] = tolower(w[i].word[j]);
        if(check(stopword, w[i].word, stopnum)) strcpy(w[i].word, "?bye");
    }
    chimuc tmp;
    for(int i = 0; i < k-1; i++)
    {
        for(int j = i+1; j < k; j++)
        {
            if(strcasecmp(w[i].word, w[j].word) > 0) 
            {
                tmp = w[j];
                w[j] = w[i];
                w[i] = tmp;
            }
        }
    }
    int clean_index = 0;
    int label;
    for(int i = 0; i < k; i++)
    {
        if(strcasecmp(w[i].word, "DTR") != 0 && strcasecmp(w[i].word, "?bye") != 0)
        {
        label = 0;
            for(int j = 0; j <= clean_index; j++)
            {
                if(strcasecmp(w[i].word, cleanword[j].word) == 0) 
                {
                    label = 1;
                    break;
                }
            }
        if(label == 0) 
        {
            strcpy(cleanword[clean_index].word, w[i].word);
            cleanword[clean_index].f = 0;
            clean_index++;
        }
        
        }
    }
    for(int i = 0; i < clean_index; i++)
    {
        for(int j = 0; j < k; j++)
        {
            if(strcasecmp(w[j].word, "DTR") != 0 && strcasecmp(w[j].word, "?bye") != 0){
            if(strcasecmp(cleanword[i].word, w[j].word) == 0)
            {
                cleanword[i].f++;
                cleanword[i].list[count(cleanword[i].list)] = w[j].list[0];
            }
            }
        }
    }
    for(int i = 0; i < clean_index; i++){
    printf("%s %d, ", cleanword[i].word, cleanword[i].f);
        for(l = 0; l < count(cleanword[i].list) -1; l++) printf("%d, ", cleanword[i].list[l]);
        printf("%d\n", cleanword[i].list[l]);
        }
}