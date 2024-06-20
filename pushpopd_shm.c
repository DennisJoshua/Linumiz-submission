#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <errno.h>

#define SHM_KEY 0x01234
#define SIZE 4
#define MAX_LENGTH 1024

typedef struct {
   int top;
   char path[SIZE][MAX_LENGTH];
}Shared_Data;

void pushd(Shared_Data *data, char *dir)
{
    if (data->top == SIZE - 1) {
        printf("Stackoverflow!\n");
    } else {
        if (chdir(dir) == 0) {
            data->top = data->top + 1;
            if (getcwd(data->path[data->top], MAX_LENGTH) == NULL) {
                printf("\nError getting current directory");
            }
       } else {
            printf("\nNo such directory");
         }
    }
}

void show(Shared_Data *data)
{
    for (int i = data->top; i >= 0; i--){
            printf("%s\n", data->path[i]);
    }
}

void popd(Shared_Data *data)
{
    if(data->top != -1){
        data->top = data->top - 1;
    } else {
	printf("Underflow!\n");
    }
}

int main(int argc, char *argv[])
{

    // Creating the Shared memory
    int shmid = shmget(SHM_KEY, sizeof(Shared_Data), IPC_CREAT | 0666);
    if (shmid == -1){
	perror("shmget");
        exit(1);
    }
    // Attaching the shared memory
    Shared_Data *data = shmat(shmid, NULL, 0);
    if (data == (Shared_Data *) -1) {
        perror("shmat");
        exit(1);
    }

    if (data->top == 0 && data->path[0][0] == '\0'){
        data->top = -1;
    }

    if (argc < 2) {
        printf("No command provided\n");
        return 1;
    } else if (strcmp(argv[1], "pushd") == 0) {
        if (argc < 3) {
            printf("No directory provided\n");
            return 1;
        }
        pushd(data, argv[2]);
    } else if (strcmp(argv[1], "popd") == 0){
	if (argc < 2) {
            printf("No directory provided\n");
            return 1;
        }
	popd(data);
    } else {
	    printf("No such command found\n");
    	}
    show(data);

   // Detaching the shared memory Data
   if (shmdt(data)==-1){
	perror("shmdt");
	exit(1);
   }

    return 0;
}
