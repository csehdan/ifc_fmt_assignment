#include <iostream>;
#include "ifcParser.h"

#define DEBUG 0

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: \" ifc_fmt infile outfile\"");
        return 1;
    }

    if (strcmp(argv[1], argv[2]) == 0)
    {
        fprintf(stderr, "Outfile should differ from infile.");
    }

    std::string param1 = argv[1];
    std::string param2 = argv[2];

    IfcParser ifcp(param1, param2);

    int read = ifcp.ReadInputFile();

    if (read > 0)
    {
        fprintf(stderr, "Input file could no be parsed.");
        return 1;
    }

    int format = ifcp.Format();

    if (format > 0)
    {
        return 2;
    }

#if DEBUG
    ifcp.PrintConsole();
#endif

    ifcp.PrintFile(param2);

    return 0;
}
