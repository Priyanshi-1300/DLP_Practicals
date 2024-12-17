#include <stdio.h>
#include<conio.h>
#include<strings.h>

int main() {
    char input[100];
  printf("Enter String: ");
  scanf("%s",input);
  int len = strlen(input);
  if (len < 2) {
        printf("Invalid String");
    }
  if (input[len-1] == 'b' && input[len-2] == 'b') {
        int accepted = 1;
        for (int i = 0; i < len - 2; i++) {
            if (input[i] != 'a') {
                accepted = 0; // Not accepted
                break;
            }
        }

        if (accepted) {
            printf("Valid String");
        } else {
            printf("Invalid String");
        }
    } else {
        printf("Invalid String");
    }
    return 0;
}
