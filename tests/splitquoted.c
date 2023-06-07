
#define RPM_GNUC_INTERNAL

#include "../include/rpm/argv.h"
#include "../rpmio/rpmmacro_internal.h"

#include <string.h>

static int verbose = 0;

static int _testCompare(ARGV_t args, const char *s1, const char *s2, const char *file, int line)
{
    int failed = strcmp(s1, s2) != 0;
    if (failed) {
        fprintf(stderr, "%s:%d error: actual '%s' expected '%s'\n", file, line, s1, s2);
        argvPrint("", args, stderr);
    }
    return failed;
}

#define testCompare(a,b,c) _testCompare(a, b, c, __FILE__, __LINE__)

int main(int argc, char **argv)
{
    ARGV_t args = NULL;
    const char *s = "-D11";
    splitQuoted(&args, s, " \t");
    if (argvCount(args) != 1 && testCompare(args, args[0], s)) {
        return 1;
    }
    argvFree(args);

    args = NULL;
    s = "-D\"11\"";
    splitQuoted(&args, s, " \t");
    if (argvCount(args) != 1 && testCompare(args, args[0], s)) {
        return 1;
    }
    argvFree(args);

    args = NULL;
    s = "-D\"44 55\"";
    splitQuoted(&args, s, " \t");
    if (argvCount(args) != 1 && testCompare(args, args[0], s)) {
        return 1;
    }
    argvFree(args);

    args = NULL;
    s = "-D \"66 77\"";
    splitQuoted(&args, s, " \t");
    if (verbose)
        argvPrint(s, args, stderr);
    if (argvCount(args) != 2 && (testCompare(args, args[0], "-D") || testCompare(args, args[1], "\"66 77\""))) {
        return 1;
    }
    argvFree(args);

    args = NULL;
    s = "-D\"44 55\" -D \"66 77\"";
    splitQuoted(&args, s, " \t");
    if (argvCount(args) != 3 && (testCompare(args, args[0], "-D\"44 55\"") || testCompare(args, args[1], "-D") || testCompare(args, args[2], "\"66 77\""))) {
        return 1;
    }
    argvFree(args);

    args = NULL;
    s = "-D'13 14'";
    splitQuoted(&args, s, " \t");
    if (argvCount(args) != 1 && testCompare(args, args[0], s)) {
        return 1;
    }
    argvFree(args);

    args = NULL;
    s = "-D '15 16'";
    splitQuoted(&args, s, " \t");
    if (argvCount(args) != 1 && testCompare(args, args[0], s)) {
        return 1;
    }
    argvFree(args);

    args = NULL;
    s = "-D11 -D 22 -D\"33\" -D\"44 55\" -D \"66 77\"";
    splitQuoted(&args, s, " \t");
    if (argvCount(args) != 7)
        argvPrint(s, args, stderr);
    argvFree(args);


    return 0;
}
