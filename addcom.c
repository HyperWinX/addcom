#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    if (argc != 3){
        printf("Incorrect usage!\nUsage:\taddcom <path_to_executable> <name_to_run>");
        return -1;
    }
    if (!fopen(argv[1], "r")){
        printf("Invalid path!");
        return -1;
    }
    char* path = "/bin/";
    char finalcommand[1536];
    strcpy(finalcommand, "ln -s ");
    strcat(finalcommand, argv[1]);
    strcat(finalcommand, " ");
    strcat(finalcommand, path);
    strcat(finalcommand, argv[2]);
    int retcode = system(finalcommand);
    switch (retcode){
        case 256:
            printf("Permission denied! Please run as root.\n");
            break;
        case 0:
            printf("Successfully created link in %s%s to %s!\n", path, argv[2], argv[1]);
            break;
        default:
            printf("Unknown error.\n");
            break;
    }
    return retcode;
}