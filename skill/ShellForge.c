#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <limits.h>
#include <errno.h>

int main() {

    char command[200];
    char hostname[100];
    char currentPath[PATH_MAX];

    /* Your roll number and name */
    char username[] = "30053_Karthik";

    /* Get laptop name */
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        strcpy(hostname, "localhost");
    }

    printf("\n");
    printf("========================================\n");
    printf("             Welcome to ShellForge\n");
    printf("========================================\n");
    printf("\n");

    while (1) {

        /* Get the current directory */
        if (getcwd(currentPath, sizeof(currentPath)) == NULL) {
            strcpy(currentPath, "?");
        }

        /* Ubuntu-style prompt with current path */
        printf("%s@%s:%s$ ",
               username,
               hostname,
               currentPath);

        /* Read command */
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

        /* Remove newline */
        command[strcspn(command, "\n")] = '\0';


        /* ==================== ls ==================== */

        if (strcmp(command, "ls") == 0) {

            DIR *dir;
            struct dirent *entry;

            dir = opendir(".");

            if (dir == NULL) {
                printf("Unable to open directory.\n");
                continue;
            }

            while ((entry = readdir(dir)) != NULL) {

                if (entry->d_name[0] != '.') {
                    printf("%-25s", entry->d_name);
                }
            }

            printf("\n");

            closedir(dir);
        }


        /* ==================== pwd ==================== */

        else if (strcmp(command, "pwd") == 0) {

            if (getcwd(currentPath, sizeof(currentPath)) != NULL) {
                printf("%s\n", currentPath);
            }
            else {
                printf("Unable to get current directory.\n");
            }
        }


        /* ==================== mkdir ==================== */

        else if (strncmp(command, "mkdir ", 6) == 0) {

            char *dirname = command + 6;

            if (strlen(dirname) == 0) {

                printf("mkdir: missing directory name\n");
            }

            else if (mkdir(dirname, 0777) == 0) {

                printf("Directory '%s' created successfully.\n", dirname);
            }

            else {

                if (errno == EEXIST) {
                    printf("mkdir: '%s' already exists.\n", dirname);
                }
                else {
                    printf("mkdir: unable to create directory '%s'.\n",
                           dirname);
                }
            }
        }


        /* ==================== cd ==================== */

        else if (strncmp(command, "cd ", 3) == 0) {

            char *dirname = command + 3;

            if (strlen(dirname) == 0) {

                printf("cd: missing directory name\n");
            }

            else if (chdir(dirname) == 0) {

                /* Get and display new path */
                if (getcwd(currentPath, sizeof(currentPath)) != NULL) {

                    printf("Changed directory to: %s\n",
                           currentPath);
                }
            }

            else {

                printf("cd: unable to access '%s'\n", dirname);
            }
        }


        /* ==================== date ==================== */

        else if (strcmp(command, "date") == 0) {

            time_t currentTime;

            time(&currentTime);

            printf("%s", ctime(&currentTime));
        }


        /* ==================== cal ==================== */

        else if (strcmp(command, "cal") == 0) {

            system("cal");
        }


        /* ==================== exit ==================== */

        else if (strcmp(command, "exit") == 0) {

            printf("Exiting ShellForge...\n");

            break;
        }


        /* ==================== Empty command ==================== */

        else if (strlen(command) == 0) {

            continue;
        }


        /* ==================== Unknown command ==================== */

        else {

            printf("ShellForge: command not found: %s\n",
                   command);
        }
    }

    return 0;
}
