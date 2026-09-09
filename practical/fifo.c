#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {

    if (mkfifo("myfifo", 0666) == -1) {
        perror("mkfifo");
        return 1;
    }

    printf("FIFO created successfully\n");

    return 0;
}
