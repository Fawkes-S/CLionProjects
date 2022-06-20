/** Algorithm & Complexity Analysis
 *
 * Statement                     # primitive operations
 * ----------------------------------------------------
 * Input a string ch of n characters
 * Output bool value
 *
 * n = strlen(ch)-1              1
 * strcpy(A, ch)                 1
 * while n > i do                n/2
 *    if A[i]!=A[n] then         n/2
 *        return false           1
 *    end if
 *    i++                        n/2
 *    n--                        n/2
 * end while
 * return true
 * ----------------------------------------------------
 * Total: 2n+3, which is O(n)
 **/
#include "stdbool.h"
#include "string.h"
#include "stdio.h"
bool isPalindrome(char A[], int len){
    int i=0;
    while(len>i){
        if(A[i]!=A[len]){
            return false;
        }
        i++;
        len--;
    }
    return true;
}
int main(){
    bool palindrome;
    char ch[BUFSIZ];
    int l;
    printf("Enter a word:");
    scanf("%s",ch);
    l = strlen(ch)-1;
    char A[l+2];
    strcpy(A, ch);
    palindrome = isPalindrome(A, l);
    if(palindrome)
        printf("yes");
    else
        printf("no");
    return 0;

}