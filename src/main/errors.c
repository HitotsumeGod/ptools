#include "ptools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *ptools_handle_error(struct errmsg *msg, project_handle_error handlr)
{
        static char res[ERRMSGMAX * 10];
        char desc[ERRMSGMAX], funcname[FUNCNAMEMAX];
        struct errmsg *old, *next, *prev = NULL;

        for (int i = 0; i < sizeof(res); i++)
                res[i] = 0;
        while (1) {
                strncpy(funcname, msg -> function_name, sizeof(funcname));
                switch (msg -> errcode.common_err) {
                case COMMON_BADARGS_ERR:
                        snprintf(desc, sizeof(desc), "%s\n%s\n", funcname, "function was passed bad arguments");                      
                        break;
                case COMMON_MALLOC_ERR:
                        snprintf(desc, sizeof(desc), "%s\n%s\n", funcname, "dynamic memory management failed due to overuse of system memory");
                        break;
                case COMMON_SOCKET_ERR:
                        snprintf(desc, sizeof(desc), "%s\n%s%d\n", funcname, "socket could not be created; errno #", errno);
                        break;
                case COMMON_BIND_ERR:
                        snprintf(desc, sizeof(desc), "%s\n%s%d\n", funcname, "could not bind socket to local address; errno#", errno);
                        break;
                case COMMON_SEND_ERR:
                        snprintf(desc, sizeof(desc), "%s\n%s%d\n", funcname, "issue with sending message from socket; errno#", errno);
                        break;
                case COMMON_RECV_ERR:
                        snprintf(desc, sizeof(desc), "%s\n%s%d\n", funcname, "issue with receiving message from socket; errno#", errno);
                        break;
                case COMMON_SUCCESS_ERR:
                        snprintf(desc, sizeof(desc), "%s\n%s\n", funcname, "function executed successfully");
                        break;
                case COMMON_PROJECT_ERR:
                        if (!msg -> errcode.project_err)
                                snprintf(desc, sizeof(desc), "ptools_handle_error() attempted to pass a project_error_code to callback but project_error_code was NULL");
                        else
                                snprintf(desc, sizeof(desc), "%s\n%s\n", funcname, handlr(msg -> errcode.project_err));
                        break;
                }
                strncat(res, desc, sizeof(res) - strlen(desc) - 1);
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
