//John Stockton
//Dr. Vineyard
//CS-231
//Winter 2022

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int fail( char str[] ) {
    fprintf( stderr, "%s Failed", str );
    return 1;
}

//TODO: Document
int main( int argc, char *argv[] ) {
    char *inputName = argv[1];
    char *outputName = argv[2];
    int wordLength = atoi( argv[3] );

    int fd[2];
    if( pipe(fd)==-1 ) { return 1; }

    int pid1 = fork();
    if( pid1<0 ) { return 2; }
    else if( pid1==0 ) {
        //Child process 1 (./wordGrab)
        dup2( fd[1], STDOUT_FILENO );
        close( fd[0] );
        close( fd[1] );
        execlp( "./wordGrab", "./wordGrab", inputName, NULL );
    }

    // int pid2 = fork();
    // if( pid2<0 ) { return 2; }
    // else if( pid2==0 ) {
    //     //Child process 2 (./lengthCheck)
    //     dup2( fd[0], STDIN_FILENO );
    //     close( fd[0] );
    //     close( fd[1] );
    //     execlp( "./lengthCheck", "./lengthCheck", wordLength, NULL );
    // }

    close( fd[0] );
    close( fd[1] );

    waitpid( pid1, NULL, 0 );
    //waitpid( pid2, NULL, 0 );
    return 0;
}