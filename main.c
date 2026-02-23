#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
//This function is used to check whether an input is a valid integer/number or not
int valid_integer(char *input) {
    if (input == NULL || *input == '\0') {
        return 0;
    }
    for (int index = 0; input[index] != '\0'; index++) {
        if (!isdigit(input[index])) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    //Ask for inputs greater than 2
    if (argc < 3) {
        printf("Please enter two numbers. Eg(11 10)");
        return 1;
    }
    //Storing our numbers from the user's input
    int first_number = atoi(argv[1]);
    int second_number = atoi(argv[2]);
    int fd[2];
    pid_t pid;
    int parent_to_child[2];
    int child_to_parent[2];
    int length = strlen(argv[1]) + strlen(argv[2]);
    //Checks for valid integers
    if (!valid_integer(argv[1]) || !valid_integer(argv[2])) {
        printf("All inputs must be integers");
        return 1;
    }
    //Checks if the integers are 4 digits
    if (strlen(argv[1]) != 4 || strlen(argv[2]) != 4) {
        printf("Please write in two 4-digit numbers");
        return 0;
    }
    //If first number is lower we will return the multiplied value
    if (strlen(argv[1]) <= 1) {
        int total = first_number * second_number;
        printf(total);
    }
    printf("Your integers are %d %d\n", first_number, second_number);

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }
    pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }
    if (pid == 0)


}