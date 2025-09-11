#include "ptools.h"
#include <stddef.h>

char *ptools_handle_error(enum common_error cerr, void *perr, project_handle_error handlr)
{
        char *res;

        switch (cerr) {
        case COMMON_BAD_ARGS_ERR:
                res = "function was passed bad arguments";
                break;
        case COMMON_MALLOC_ERR:
                res = "dynamic memory management failed due to overuse of system memory";
                break;
        case COMMON_PROJECT_ERR:
                if (!perr)
                        res = "ptools_handle_error() attempted to pass a project_error_code to callback but project_error_code was NULL";
                else
                        res = handlr(perr);
                break;
        default:
                res = NULL;
        }
        return res;
}