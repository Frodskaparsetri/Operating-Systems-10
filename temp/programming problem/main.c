#include <unistd.h> /* For write() and STDOUT_FILENO */
#include <stdlib.h> /* For EXIT_SUCCESS and EXIT_FAILURE */
#include <sys/stat.h> // For fstat()

#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/types.h>

int main(void) {
        char inputIn[255];
        char inputOut[255];


        // input file
        char input_text[] = "Path to input file: ";        
        write(STDOUT_FILENO, input_text, sizeof(input_text) - 1);
        read(STDOUT_FILENO, inputIn, sizeof(inputIn) - 1);

        // output file
        char output_text[] = "output filename: ";
        write(STDOUT_FILENO, output_text, sizeof(output_text) - 1);
        read(STDOUT_FILENO, inputOut, sizeof(inputOut) - 1);


        // Read content from input file
        struct stat inputFileStat;
        int inputFileDescriptor = open(inputIn, O_RDONLY);

        fstat(inputFileDescriptor, &inputFileStat);
        char *buff = malloc(inputFileStat.st_size + 1);

        // Create output file
        int createStatus = creat(inputOut, O_CREAT);


        return EXIT_SUCCESS; 
}
