#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
// Concepts used : process (fork, exec), file (writing)

int main()
{
    int times;
    printf("Enter the number of times to fork\n");
    scanf("%d", &times);
    
    int fd = open("./output.txt", O_CREAT|O_RDWR|O_TRUNC, 0666);
    char buff[64];
    int first_parent = getpid();
    sprintf(buff, "PARENT %d CHILD %d\n", getppid(), first_parent);
    write(fd, buff, strlen(buff));
    
    int i;
    // Usage of fork
    for(i = 0; i < times; i++)
    {
        int pid = fork();
        // Usage of file
        if(pid != 0)
        {
            wait(pid);
            sprintf(buff, "PARENT %d CHILD %d\n", getpid(), pid);
            write(fd, buff, strlen(buff));
        }
    }

    // using execl to spawn a process
    if(getpid() == first_parent)
    {
        if(fork() == 0)
        {
            printf("fork and exec\n");
            execl("python", "python", "./tree_generator.py", (char*)0);
        }    
    }

    return 0;
}