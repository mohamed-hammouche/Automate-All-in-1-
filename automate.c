#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int inArray(char A[] , char x , int n){
    int i;
    for (i = 0 ; i<n ; i++){
        if (A[i] == x){ 
            return 1;
        }
    }
    return 0 ;
}

int main() {
    int l, ml, nc, i, j, po = 0 , x; 
    char chars[100], pre[100], suff[100] ,t;  
    
    printf("How many characters will you insert: \n");
    scanf("%d", &nc);
    printf("Enter the characters: \n");
    
    for (i = 0; i < nc; i++) {
        scanf(" %c",&t);
        x=inArray(chars , t , i);
        if(x == 1){
            printf("the character is already in the array\n");
            i--;
        }else{
            chars[i] = t ;
        }
    }

    printf("Enter the minimum length of the word you want to generate: \n");
    do {
        scanf("%d", &ml);
    } while (ml < 0);

    printf("Enter the maximum length of the word you want to generate: \n");
    do {
        scanf("%d", &l);
    } while (l < ml);

    printf("---------------------------------\n");
    printf("The program will generate words using the following characters: \n");
    for (i = 0; i < nc; i++) {
        printf("%c ", chars[i]);
    }
    printf("\nMinimum word length: %d", ml);
    printf("\nMaximum word length: %d\n", l);
    printf("---------------------------------\n");

    char A[1000][l + 1];  

    printf("The generated words: \n");

    for (int len = ml; len <= l; len++) {
        int total_words = pow(nc, len);
        for (int i = 0; i < total_words; i++) {
            int temp = i;
            for (int j = 0; j < len; j++) {
                A[po][j] = chars[temp % nc];  
                temp /= nc;
            }
            A[po][len] = '\0';  
            po++;  
        }
    }

    for (int i = 0; i < po; i++) {
        printf("'%s' ", A[i]);
    }

    while (getchar() != '\n');

    printf("\nEnter the prefix: - type enter to skip - \n");
    fgets(pre, sizeof(pre), stdin);
    pre[strcspn(pre, "\n")] = '\0';  

    printf("\nEnter the suffix: - type enter to skip - \n");
    fgets(suff, sizeof(suff), stdin);
    suff[strcspn(suff, "\n")] = '\0';  

    printf("\nThe words containing the prefix:\n");
    if (pre[0] == '\0') {
        printf("\nYou didn't enter any prefix\n");
    } else {
        int found = 0;
        for (int i = 0; i < po; i++) {
            if (strlen(A[i]) >= strlen(pre) && strncmp(A[i], pre, strlen(pre)) == 0) {  
                printf("%s ", A[i]);
                found = 1;
            }
        }
        if (found == 0) printf("No words found with prefix.\n");  
    }

    printf("\nThe words containing the suffix:\n");
    if (suff[0] == '\0') {
        printf("\nYou didn't enter any suffix\n");
    } else {
        int found = 0;
        for (int i = 0; i < po; i++) {
            if (strlen(A[i]) >= strlen(suff) && strcmp(A[i] + (strlen(A[i]) - strlen(suff)), suff) == 0) {  
                printf("%s ", A[i]);
                found = 1;
            }
        }
        if (found == 0) printf("No words found with suffix.\n");  
    }

    
        printf("\nThe words containing both prefix and suffix:\n");
        int found = 0;
        for (int i = 0; i < po; i++) {
            if (strlen(A[i]) >= strlen(pre) && strncmp(A[i], pre, strlen(pre)) == 0) { 
                if (strlen(A[i]) >= strlen(suff) && strcmp(A[i] + (strlen(A[i]) - strlen(suff)), suff) == 0) {
                    printf("%s ", A[i]);
                    found = 1;
                }
            }
        }
        if (found == 0) printf("No words found with prefix and suffix\n"); 

    

    printf("\n-------------- Grammaires --------------\n");
    char terminals[100], non_terminals[100], input[10],axiom[100] ,Ls[100], Rs[100] ;
    int num_terminals, num_non_terminals, NR;
    int type3 , type2 , type1 ;

    printf("Enter number of terminals: ");
    do {
        scanf("%d", &num_terminals);
    } while (num_terminals < 0);
    getchar();

    for (int i = 0; i < num_terminals; i++) {
        printf("Terminal %d: ", i + 1);
        scanf(" %c", &t);
        x = inArray(terminals, t, i);
        if (x == 1) {
            printf("The entered terminal is already in the array\n");
            i--;
        } else {
            terminals[i] = t;
        }
    }
    getchar();
    printf("Enter number of non-terminals: ");
    do {
        scanf("%d", &num_non_terminals);
    } while (num_non_terminals < 0);

    getchar();
    printf("(The first one is the axiom by default!)\n");

    for (int i = 0; i < num_non_terminals; i++) {
        while (1) {
            printf("Non-terminal %d (format <X>): ", i + 1);
            scanf("%s", input);

            if (strlen(input) == 3 && input[0] == '<' && input[2] == '>' && isalpha(input[1])) {
                t = input[1];
                x = inArray(non_terminals, t, i);
                if (x == 1) {
                    printf("The entered non-terminal '%c' is already in the array.\n", t);
                } else {
                    non_terminals[i] = t;
                    break;
                }
            } else {
                printf("Invalid format. Please use <X> where X is a letter.\n");
            }
        }
    }
    axiom[0] = non_terminals[0];
    axiom[1] = '\0';

    printf("\nAxiom: <%c>\n", axiom[0]);
    printf("All non-terminals: ");
    for (int i = 0; i < num_non_terminals; i++) {
        printf("<%c> ", non_terminals[i]);
    }
    printf("\nAll terminals: ");
    for (int i = 0; i < num_terminals; i++) {
        printf("%c ", terminals[i]);
    }

printf("\n-----------\n");

printf("Enter number of production rules: ");
scanf("%d", &NR);
getchar();

for (int i = 0; i < NR; i++) {
    printf("Rule %d\n", i + 1);

    while (1) {
        printf("  Ls: ");
        fgets(Ls, sizeof(Ls), stdin);
        Ls[strcspn(Ls, "\n")] = '\0';

        int found_non_terminal = 0;
        for (int j = 0; j < strlen(Ls); j++) {
            if (Ls[j] == '<' && j + 2 < strlen(Ls) && Ls[j+2] == '>') {
                if (inArray(non_terminals, Ls[j+1], num_non_terminals)) {
                    found_non_terminal = 1;
                    break;
                }
            }
        }

        if (!found_non_terminal) {
            printf("Left side must include at least one valid non-terminal in format <X>\n");
        } else {
            break;
        }
    }

    while (1) {
        printf("  Rs: ");
        fgets(Rs, sizeof(Rs), stdin);
        Rs[strcspn(Rs, "\n")] = '\0';

        int valid = 1;
        for (int j = 0; j < strlen(Rs); j++) {
            if (Rs[j] == '<' && j + 2 < strlen(Rs) && Rs[j+2] == '>') {
                if (!inArray(non_terminals, Rs[j+1], num_non_terminals)) {
                    valid = 0;
                    break;
                }
                j += 2;
            } else if (!inArray(terminals, Rs[j], num_terminals)) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("Right side contains invalid symbols (not in terminals or non-terminals)\n");
        } else {
            break;
        }
    }

    
    printf("  Rule %d: %s -> %s\n", i + 1, Ls, Rs);
}


   

}
