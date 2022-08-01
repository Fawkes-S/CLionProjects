#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX_LEN 10
#define N       150
typedef char *string;
int main()
{
    string a = malloc(sizeof (string));
    string b = malloc(sizeof (string));
    strcpy(a,"bys");
    strcpy(b,"ads");
    string temp = malloc(sizeof(string));
    //遍历所有国家名称

    if(strcmp(a,b) > 0)  // b<a, exchage
    {
        strcpy(temp,b);
        strcpy(b,a);
        strcpy(a,temp);
    }
    printf("%s", a);
}
