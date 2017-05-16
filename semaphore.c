#include <stdio.h>
#include <sys/sem.h>

void main()
{
    int key = ftok("key.txt", 8);
    int id = semget(key, 1, IPC_CREAT|0666);
    // struct sembuf
    // {
    //     ushort_t sem_num;
    //     short sem_op;
    //     short sem_flg;
    // };

    int pid = fork();

    if(pid == 0)
    {
        printf("child waiting for semaphore\n");
        struct sembuf s1;
        s1.sem_num = 0;
        s1.sem_op = -1;
        s1.sem_flg = 0;
        if(semop(id, &s1, 1) == -1)
            printf("fail");
        printf("child got lock\n");
        sleep(2);
    }

    else
    {
        printf("parent waiting for semaphore\n");
        printf("parent got lock\n");
        sleep(2);
        struct sembuf s1;
        s1.sem_num = 0;
        s1.sem_op = 1;
        s1.sem_flg = 0;
        semop(id, &s1, 1);
    }
}
