#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

void getPassword(char *password, int maxLength) {
    struct termios oldt, newt;
    int i = 0;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (read(STDIN_FILENO, &ch, 1) == 1 && ch != '\n' && i < maxLength - 1) {
        if (ch == 127 || ch == 8) { 
            if (i > 0) {
                i--;
                printf("\b \b");
                fflush(stdout);
            }
        } else {
            password[i++] = ch;
            printf("*");
            fflush(stdout);
        }
    }
    password[i] = '\0';

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    printf("\n");
}

int main() {
    const char correct_password[] = "admin123";
    char password[100];
    int attempts = 0;
    int max_attempts = 3;

    while (attempts < max_attempts) {
        printf("Enter password: ");
        fflush(stdout);
        getPassword(password, sizeof(password));

        if (strcmp(password, correct_password) == 0) {
            printf("Login successful\n");
            break;
        } else {
            attempts++;
            int attempts_left = max_attempts - attempts;
            if (attempts_left > 0) {
                printf("Incorrect password. Attempts left: %d\n", attempts_left);
            } else {
                printf("Access denied\n");
            }
        }
    }

    return 0;
}
