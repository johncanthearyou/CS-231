//John Stockton
//Dr. Vineyard
//CS-231
//Winter 2022

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define PIPE_ERROR 1
#define FORK_ERROR 2

//Main is an orchestrator function designed to pipe multiple processes together
//    it will take 3 parameters, the name of the input file, the name of the
//    output file, and the the length of words we want to keep 
//1. Main creates 3 pipes which all the children processes will inheirit
//2. Main forks a child which will call ./wordGrab, giving it the name of the 
//   input file from which to read, piping the output of wordGrab to the next
//   child, ./lengthCheck
//3. Main forks a child which will call ./lengthCheck, giving it the length 
//   of words that we want to keep, whose input is piped from ./wordGrab and
//   whose output is piped to the next child, ./reverse
//4. Main forks a child which will call ./reverse, which takes no parameters,
//   whose input is piped from ./lengthCheck and whose output is piped to the
//   next child, ./caseWorker
//5. Main forks the final child which will call ./caseWorker, giving it the
//   name of the file to which we will write, whose input is piped from 
//   ./lengthCheck and whose output is written to a file
int main( int argc, char *argv[] ) {
    //Argument variables
    char *inputName = argv[1];
    char *outputName = argv[2];
    char *wordLength = argv[3];

    //Control variables
    int numChildren = 4;
    int childProcess[numChildren];
    int numPipes = numChildren-1;
    int fd[numPipes][2];
    int i;

    //Initialize the pipes in parent
    //  These will all be inheiriated to parent
    for( i=0; i<numPipes; i++ ) {
        if( pipe(fd[i])==-1 ) {
            //Failure creating pipe, kill created pipes
            for( i=i; i>=0; i-- ) {
                close( fd[i][0] );
                close( fd[i][1] );
            }
            exit(PIPE_ERROR);
        }
    }

    childProcess[0] = fork();
    if( childProcess[0]<0 ) { 
        //Failed the fork, kill pipes
        for( i=0; i<numPipes; i++ ) {
            close( fd[i][0] );
            close( fd[i][1] );
        }
        exit(FORK_ERROR);
    } else if( childProcess[0]==0 ) {
        //Child process 1 (./wordGrab)
        //reroute output to write end of first pipe
        dup2( fd[0][1], STDOUT_FILENO );
        //close inheirited pipes
        for( i=0; i<numPipes; i++ ) {
            close( fd[i][0] );
            close( fd[i][1] );
        }
        //execute wordGrab
        execlp( "./wordGrab", "./wordGrab", inputName, NULL );
    }

    childProcess[1] = fork();
    if( childProcess[1]<0 ) { 
        //Failed the fork, kill pipes
        for( i=0; i<numPipes; i++ ) {
            close( fd[i][0] );
            close( fd[i][1] );
        }
        exit(FORK_ERROR);
    } else if( childProcess[1]==0 ) {
        //Child process 2 (./lengthCheck)
        //reroute input from the read end of the first pipe
        dup2( fd[0][0], STDIN_FILENO );
        //reroute output from the write end of the second pipe
        dup2( fd[1][1], STDOUT_FILENO );
        //close inheirited pipes
        for( int i=0; i<numPipes; i++ ) {
            close( fd[i][0] );
            close( fd[i][1] );
        }
        //execute lengthCheck
        execlp( "./lengthCheck", "./lengthCheck", wordLength, NULL );
    }

    childProcess[2] = fork();
    if( childProcess[2]<0 ) { 
        //Failed the fork, kill pipes
        for( i=0; i<numPipes; i++ ) {
            close( fd[i][0] );
            close( fd[i][1] );
        }
        exit(FORK_ERROR);
    } else if( childProcess[2]==0 ) {
        //Child process 3 (./reverse)
        //reroute input from the read end of the second pipe
        dup2( fd[1][0], STDIN_FILENO );
        //reroute output from the write end of the third pipe
        dup2( fd[2][1], STDOUT_FILENO );
        //close inheirited pipes
        for( i=0; i<numPipes; i++ ) {
            close( fd[i][0] );
            close( fd[i][1] );
        }
        //execute reverse
        execlp( "./reverse", "./reverse", NULL );
    }

    childProcess[3] = fork();
    if( childProcess[3]<0 ) { 
        //Failed the fork, kill pipes
        for( i=0; i<numPipes; i++ ) {
            close( fd[i][0] );
            close( fd[i][1] );
        }
        exit(FORK_ERROR);
    } else if( childProcess[3]==0 ) {
        //Child process 4 (./caseWorker)
        //reroute input from the read end of the third pipe
        dup2( fd[2][0], STDIN_FILENO );
        //close inheirited pipes
        for( i=0; i<numPipes; i++ ) {
            close( fd[i][0] );
            close( fd[i][1] );
        }
        //execute caseWorker
        execlp( "./caseWorker", "./caseWorker", outputName, NULL );
    }

    //close pipes in the parent
    for( i=0; i<numPipes; i++ ) {
        close( fd[i][0] );
        close( fd[i][1] );
    }

    //Make parent wait for child processes before exiting
    for( i=0; i<4; i++ ) {
        waitpid( childProcess[i], NULL, 0 );
    }
}