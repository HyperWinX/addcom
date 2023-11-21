#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){
    if (argc == 2 && strcmp(argv[1], "install") == 0){
        char current_path[1024];
        if (getcwd(current_path, sizeof(current_path)) == NULL){
            fprintf(stderr, "Cannot get current directory, please install program yourself or run as root.\n");
            return -1;
        }
        strcat(current_path, "/");
        strcat(current_path, argv[0]);
        char command[1536];
        strcpy(command, "cp ");
        strcat(command, current_path);
        strcat(command, " /bin/addcom > /dev/null");
        printf(command);
        scanf(NULL);
        int retcode = system(command);
        switch (retcode){
            case -1:
                fprintf(stderr, "Installation failure!\n");
                return -1;
            case 0:
                fprintf(stdout, "Installation successful!\n");
                return 0;
        }
    }
    if (argc != 3){
        printf("Incorrect usage!\nUsage:\taddcom <path_to_executable> <name_to_run>\n");
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