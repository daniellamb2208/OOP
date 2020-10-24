#include "mytar.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
        std::cerr << "mytar: tar list requires an argument" << std::endl
                  << "Try give a tar file to check the program" << std::endl;
    else if (parsecmd(argc, argv))
        load(argv[1]);

    return 0;
}