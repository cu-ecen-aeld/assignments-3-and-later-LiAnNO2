#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }

    char *writefile = argv[1];
    char *writestr = argv[2];

    if (writefile[0] == '\0' || writestr[0] == '\0') {
        return 1;
    }

    char *directory = dirname(writefile);
    if (access(directory, F_OK) == -1) {
        if (mkdir(directory, 0777) == -1) {
	    //fprintf(stderr, "Error: Failed to create directory\n");
            return 1;
        }
    }

    FILE *file = fopen(writefile, "w");
    if (file == NULL) {
        //fprintf(stderr, "Error: Failed to open file\n");
        return 1;
    }

    if (fprintf(file, "%s\n", writestr) < 0) {
        //fprintf(stderr, "Error: Failed to write to file\n");
        fclose(file);
        return 1;
    }

    fclose(file);
    //printf("Content written to %s successfully.\n", writefile);
    return 0;
}
