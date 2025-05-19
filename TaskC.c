#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

void getPassword(char *password, int maxLength) {
    struct termios oldt, newt;
    int i = 0;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while ((read(STDIN_FILENO, &ch, 1) == 1) && ch != '\n' && i < maxLength - 1) {
        if (ch == 127 || ch == 8) {  
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            password[i++] = ch;
            printf("*");
        }
        fflush(stdout);
    }
    password[i] = '\0';

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    printf("\n");
}

int main() {
    char password[100];

    while (1) {
        printf("Enter password: ");
        fflush(stdout);
        getPassword(password, sizeof(password));

        if (strcmp(password, "default123") == 0) {
            printf("Access granted\n");
            break;
        } else {
            printf("Incorrect password, try again.\n");
        }
    }

    return 0;
}
