/** 
 * Error handling API for peter projects.
*/

#ifndef __ERRORS_H__
#define __ERRORS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERRMSGMAX       2400
#define FUNCNAMEMAX     40
#define ERREP_ERR       "ERREP() failed; system memory critical"

#define ERREP(rep, func, err, msg)                                    \
        if ((rep = malloc(sizeof(struct errep))) != NULL) {           \
                rep -> caller = func;                                 \
                if (err) {                                            \
                        rep -> is_error = true;                       \
                        rep -> report.errmsg = msg;                   \
                } else {                                               \
                        rep -> is_error = false;                      \
                        rep -> report.res = msg;                      \
                }                                                     \
                rep -> next = NULL;                                   \
        }

struct errep {
        char                 *caller;
        bool                 is_error;
        union {
                char                *errmsg;
                byte                res;
        } report;
        struct errep         *next;
};

extern char *ptools_format_errors(struct errep *linked_list);

#endif //__ERRORS_H__
