#include "mytar.h"

int main(int argc, char *argv[])
{
    if (parsecmd(argc, argv))
        load(argv[1]);
    return 0;
}