#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_LENGTH 1024
#define TEXT_FORMAT_STRING "%[^\n]%*c"

int *lastOccurrence(char *pattern, char *alphabet){
    int lenP = strlen(pattern);
    int lenA = strlen(alphabet);
    int *loc = calloc(127, sizeof(int));

    for (int i = 0; i < lenA; i++) {
        *(loc + (int)(*(alphabet + i))) = -1;
    }

    for (int j = lenP - 1; j > -1; j--){
        if( *(loc + (int)(*(pattern + j))) < j){
            *(loc + (int)(*(pattern + j))) = j;
        }
    }
    // O(lenP+lenA)
    return loc;
}

int BoyerMooreMatch(char *text, char *pattern, char *alphabet){
    int lenText = strlen(text);  //n
    int lenPattern = strlen(pattern);  //m
    int *L = lastOccurrence(pattern, alphabet);
    int i,j;
    i = j = lenPattern - 1;
    do {
        if(*(text + i) == *(pattern + j)){
            if(j == 0){
                printf("\n");
                for (int k = 0; k < strlen(alphabet); k++) {
                    printf("L[%c] = %d\n", *(alphabet + k), *(L+ (int)(*(alphabet + k)) ));
                }
                return i;
            }else{
                i--;
                j--;
            }
        }else{
            i += lenPattern - (j < ( 1 + *(L + (int)(*(text + i)))) ? j:( 1 + *(L + (int)(*(text + i)))));
            j = lenPattern - 1;
        }
    } while (i < lenText);

    printf("\n");
    for (int k = 0; k < strlen(alphabet); k++) {
        printf("L[%c] = %d\n", *(alphabet + k), *(L+ (int)(*(alphabet + k)) ));
    }
    return -1;
}

int main(){
    char text[MAX_TEXT_LENGTH];
    char *pattern = malloc(127);
    char *alphabet = malloc(127);
    printf("Enter alphabet: ");
    scanf(TEXT_FORMAT_STRING, alphabet);
    printf("Enter text: ");
    scanf(TEXT_FORMAT_STRING, text);
    printf("Enter pattern: ");
    scanf(TEXT_FORMAT_STRING, pattern);

    int res = BoyerMooreMatch(text, pattern, alphabet);
    if( res == -1){
        printf("\nNo match.");
    }else{
        printf("\nMatch found at position %d.", res);
    }
    return 0;
}