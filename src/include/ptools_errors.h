/** 
 * Error handling API for peter projects.
*/

#ifndef __PTOOLS_ERRORS_H__
#define __PTOOLS_ERRORS_H__

#include <stdio.h>
#include <stdlib.h>

#define ERRMSGMAX       2400
#define FUNCNAMEMAX     40
#define FILL_ERREP_ERR  "FILL_ERREP failed; system memory critical"

#define FILL_ERREP(rep, func, err)                                    \
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

#endif //__PTOOLS_ERRORS_H__
