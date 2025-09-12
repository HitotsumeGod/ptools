#include "ptools.h"
#include <string.h>
#include <errno.h>

char *ptools_handle_error(enum common_error cerr, void *perr, project_handle_error handlr)
{
        static char res[ERRMSGMAX];

        for (int i = 0; i < sizeof(res), i++)
                res[i] = 0;
        switch (cerr) {
        case COMMON_BAD_ARGS_ERR:
                snprintf(res, sizeof(res), "function was passed bad arguments");
                break;
        case COMMON_MALLOC_ERR:
                snprintf(res, sizeof(res), "dynamic memory management failed due to overuse of system memory");
                break;
        case COMMON_SOCKET_ERR:
                snprintf(res, sizeof(res), "socket could not be created; errno #%d", errno);
                break;
        case COMMON_BIND_ERR:
                snprintf(res, sizeof(res), "could not bind socket to local address; errno#%d", errno);
                break;
        case COMMON_SEND_ERR:
                snprintf(res, sizeof(res), "issue with sending message from socket; errno#%d", errno);
                break;
        case COMMON_RECV_ERR:
                snprintf(res, sizeof(res), "issue with receiving message from socket; errno#%d", errno);
                break;
        case COMMON_PROJECT_ERR:
                if (!perr)
                        snprintf(res, sizeof(res), "ptools_handle_error() attempted to pass a project_error_code to callback but project_error_code was NULL");
                else
                        strncpy(res, handlr(perr), sizeof(res));
                break;
        }
        return res;
}
