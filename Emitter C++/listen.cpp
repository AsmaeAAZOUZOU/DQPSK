#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>
#include <signal.h>
#include <stdio.h>


using namespace std;

int temps_ecoute = 1;

int main() {
    pid_t pid;

    pid = fork();
    if(pid == 0) { // child process
        setpgid(getpid(), getpid());
        system("hackrf_transfer -r signal_ecoute.raw -f 1278000000 -s 3000000 -l 24 -g 24  -d 000000000000000075b068dc317bae07");
    } else {   // parent process
        sleep(temps_ecoute);
        printf("Sleep returned\n");
        kill(-pid, SIGKILL);
        printf("killed process group %d\n", pid);
        
    }
    exit(0);
}
