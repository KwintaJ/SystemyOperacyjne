#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "printIDs.h"

int main()
{
    printIDs(); // wypisanie identyfikatorow biezacego procesu
    return 0;
}