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
    //Storing our numbers from the user's input
    int first_number = atoi(argv[1]);
    int second_number = atoi(argv[2]);
    int fd[2];
    pid_t pid;
    int parent_to_child[2];
    int child_to_parent[2];
    int a1 = first_number / 100;
    int a2 = first_number % 100;
    int b1 = second_number / 100;
    int b2 = second_number % 100;
    int length = strlen(argv[1]) + strlen(argv[2]);
    printf("Your integers are %d %d\n", first_number, second_number);
    //If first number is lower we will return the multiplied value
    if (strlen(argv[1]) <= 1) {
        int total = first_number * second_number;
        printf("%d", total);
    }

    if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
        perror("Pipe failed");
        return 1;
    }
    pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }
    if (pid == 0) {
        int number_one, number_two, total;
        // Unused pipes that the child will not read and write from
        close(parent_to_child[1]); 
        close(child_to_parent[0]); 

        // read the values from our pipes and calculates total from number_one and number_two
        read(parent_to_child[0], &number_one, sizeof(int));
        read(parent_to_child[0], &number_two, sizeof(int));
        total = number_one * number_two;
        // send back to parent
        write(child_to_parent[1], &total, sizeof(int));
        printf("Child (PID %d): Sending %d to parent\n", getpid(), total);

        // read the values from our pipes and calculates total from number_one and number_two
        read(parent_to_child[0], &number_one, sizeof(int));
        read(parent_to_child[0], &number_two, sizeof(int));
        total = number_one * number_two;
        // send back to parent
        write(child_to_parent[1], &total, sizeof(int));
        printf("Child (PID %d): Sending %d to parent\n", getpid(), total);

        // read the values from our pipes and calculates total from number_one and number_two
        read(parent_to_child[0], &number_one, sizeof(int));
        read(parent_to_child[0], &number_two, sizeof(int));
        total = number_one * number_two;
        // send back to parent
        write(child_to_parent[1], &total, sizeof(int));
        printf("Child (PID %d): Sending %d to parent\n", getpid(), total);

        // read the values from our pipes and calculates total from number_one and number_two
        read(parent_to_child[0], &number_one, sizeof(int));
        read(parent_to_child[0], &number_two, sizeof(int));
        total = number_one * number_two;
        // send back to parent
        write(child_to_parent[1], &total, sizeof(int));
        printf("Child (PID %d): Sending %d to parent\n", getpid(), total);

        close(parent_to_child[0]);
        close(child_to_parent[1]);
        exit(0);
    }
    else {

        // Close unused ends
        close(parent_to_child[0]); 
        close(child_to_parent[1]); 

        int result_one, result_two, result_three, result_four;
        
        /// Calculating A
        printf("\n###\n# Calculating X\n###\n");
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a1);
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b1);
        // Send a1 and b1 back to our pipes for the the children pipes to use
        write(parent_to_child[1], &a1, sizeof(int));
        write(parent_to_child[1], &b1, sizeof(int));
        // Read back result_one that is stored inside our child_to_parent pipe
        read(child_to_parent[0], &result_one, sizeof(int));
        printf("Parent: Received %d from child\n", result_one);
        
        // Calculating B
        printf("\n###\n# Calculating Y\n###\n");
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a2);
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b1);
        // Send a1 and b2 back to our pipes for the the children pipes to use
        write(parent_to_child[1], &a2, sizeof(int));
        write(parent_to_child[1], &b1, sizeof(int)); 
        // Read back result_one that is stored inside our child_to_parent pipe
        read(child_to_parent[0], &result_two, sizeof(int));
        printf("Parent: Received %d from child\n", result_two);

        // Calculating C
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a1);
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b2);
        // Send a1 and b2 back to our pipes for the the children pipes to use
        write(parent_to_child[1], &a1, sizeof(int));
        write(parent_to_child[1], &b2, sizeof(int));
        // Read back result_one that is stored inside our child_to_parent pipe
        read(child_to_parent[0], &result_three, sizeof(int));
        printf("Parent: Received %d from child\n", result_three);

        // Calculating D
        printf("\n###\n# Calculating Z\n###\n");
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a2);
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b2);
        // Send a2 and b2 back to our pipes for the the children pipes to use
        write(parent_to_child[1], &a2, sizeof(int)); 
        write(parent_to_child[1], &b2, sizeof(int));
        // Read back result_one that is stored inside our child_to_parent pipe
        read(child_to_parent[0], &result_four, sizeof(int));
        printf("Parent: Received %d from child\n", result_four);

        //Calculating the sum
        long X = result_one * 10000;
        long Y = (result_two + result_three) * 100;
        long Z = result_four;
        long sum = X + Y + Z;
        //Returns the final print to return the sum
        printf("\n%d*%d == %ld + %ld + %ld == %ld\n", first_number, second_number, X, Y, Z, sum);

        wait(NULL); 
        close(parent_to_child[1]);
        close(child_to_parent[0]);
        return 1;
    }


}