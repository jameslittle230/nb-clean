#include "man.h"

const char* MAN_LOG_PATH = "../data/log/manlog";
int lockFD = 0;
man::Man* instance;

void cleanup() {
    // Give man a chance to clean up behind it, i.e. close camera driver gracefully
    flock(lockFD, LOCK_UN);

    fflush(stderr);
    fflush(stdout);
    fclose(stdout);

    if (instance) delete instance;
}

void handler(int signal)
{
    cleanup();
    exit(0);
}

void error_signal_handler(int signal) {
    char buffer[1000];

    char * sigstr = strsignal(signal);
    snprintf(buffer, 1000, "error_signal_handler() SIGNALLED: %s\n", sigstr);
    fprintf(stdout, "%s", buffer);
    fprintf(stderr, "%s", buffer);
    fflush(stdout);
    fflush(stderr);

    abort();
}

// Deal with lock file. To ensure that we only have ONE instance of man
void establishLock()
{
    lockFD = open("/home/nao/nbites/nbites.lock", O_CREAT | O_RDWR, 0666);
    if (lockFD < 0) {
        int err = errno;
        std::cout << "Could not open lockfile" << std::endl;
        std::cout << "Errno is: " << err << std::endl;
        exit(0);
    }

    int result = flock(lockFD, LOCK_EX | LOCK_NB);
    if (result == -1) {
        std::cout << "Could not establish lock on lock file. Is man already running?" << std::endl;
        exit(0);
    }
}

int main() {
    signal(SIGTERM, handler);
    signal(SIGINT, handler);

    establishLock();

    signal(SIGSEGV, error_signal_handler);

    //it is somewhat important that we write to the old file descriptors before reopening.
    //this copies some stdout buffer behavior to the new file description.
    printf("Man re-opening stdout...\n");
    fprintf(stderr, "Man re-opening stderr...\n");

    //Make stdout's fd point to a file description for the manlog file (MAN_LOG_PATH)
    freopen(MAN_LOG_PATH, "w", stdout);

    //Send stderr to whatever stdout's fd describes
    dup2(STDOUT_FILENO, STDERR_FILENO);
    
    // Constructs an instance of man. If we get here we have a lock
    instance = new man::Man();

    while (1) {
        int status;
        while ((waitpid(-1, &status, WNOHANG|WUNTRACED)) > 0);
    }

    return 1;
}
