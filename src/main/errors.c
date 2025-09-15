#include "ptools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *ptools_handle_error(struct errmsg *msg, project_handle_error handlr)
{
        static char res[ERRMSGMAX];
        char funcname[FUNCNAMEMAX];
        struct errmsg *old;

        for (int i = 0; i < sizeof(res); i++)
                res[i] = 0;
        while (1) {
                strncpy(funcname, msg -> function_name, sizeof(funcname));
                switch (msg -> errcode.common_err) {
                case COMMON_BADARGS_ERR:
                        snprintf(res, sizeof(res), "%s\n%s", funcname, "function was passed bad arguments");
                        break;
                case COMMON_MALLOC_ERR:
                        snprintf(res, sizeof(res), "%s\n%s", funcname, "dynamic memory management failed due to overuse of system memory");
                        break;
                case COMMON_SOCKET_ERR:
                        snprintf(res, sizeof(res), "%s\n%s%d", funcname, "socket could not be created; errno #", errno);
                        break;
                case COMMON_BIND_ERR:
                        snprintf(res, sizeof(res), "%s\n%s%d", funcname, "could not bind socket to local address; errno#", errno);
                        break;
                case COMMON_SEND_ERR:
                        snprintf(res, sizeof(res), "%s\n%s%d", funcname, "issue with sending message from socket; errno#", errno);
                        break;
                case COMMON_RECV_ERR:
                        snprintf(res, sizeof(res), "%s\n%s%d", funcname, "issue with receiving message from socket; errno#", errno);
                        break;
                case COMMON_PROJECT_ERR:
                        printf("%d\n", *((int *) msg -> errcode.project_err));
                        if (!msg -> errcode.project_err)
                                snprintf(res, sizeof(res), "ptools_handle_error() attempted to pass a project_error_code to callback but project_error_code was NULL");
                        else
                                snprintf(res, sizeof(res), "%s\n%s", funcname, handlr(msg -> errcode.project_err));
                        break;
                }
                old = msg;
                if (msg -> next) {
                        msg = msg -> next;
                        free(old);
                } else {
                        free(old);
                        break;
                }
        }
        return res;
}
