#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libmanagefiles.h"

int main(int argc, char *argv[]) {

    int option;

    while ((option = getopt (argc, argv, "iamxrch")) != -1) {
        switch (option) {
            case 'i':
                inclusaoDeArquivo(argc, argv);
                break;

            case 'a':
                break;

            case 'm':
                break;

            case 'x':
                break;

            case 'r':
                break;

            case 'c':
                break;

            case 'h':
                break;
            
            default:
                break;
        }
    }

    return 0;
}