/** 
 * Error handling API for peter projects.
*/

#ifndef __ERRORS_H__
#define __ERRORS_H__

#include <stdio.h>
#include <stdlib.h>

#define ERRMSGMAX       2400
#define FUNCNAMEMAX     40
#define ERREP_ERR       "ERREP() failed; system memory critical"

#define ERREP(rep, func, err)                                         \
        if ((rep = malloc(sizeof(struct errep))) != NULL) {           \
                rep -> caller = func;                                 \
                rep -> msg = err;                                     \
                rep -> next = NULL;                                   \
        }

struct errep {
        char *caller;
        char *msg;
        struct errep *next;
};

extern char *ptools_format_errors(struct errep *linked_list);

#endif //__ERRORS_H__
