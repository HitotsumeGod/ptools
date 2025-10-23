#include "ptools.h"
#include <string.h>

bool ptools_is_error(struct errep *list)
{
        if (!list)
                return true;
        return list -> is_error;
}

byte ptools_get_enumcode(struct errep *list)
{
        if (!list)
                return 0;
        return list -> report.res;
}

char *ptools_format_errors(struct errep *list)
{
        static char res[ERRMSGMAX * 10];
        static int reslen = 0;
        struct errep *old;

        if (!list)
                return "no errep provided; cause most likely FILL_ERREP failure due to system memory overuse";
        for (int i = 0; i < reslen; i++)
                res[i] = 0;
        while (list) {
                strncat(res, list -> caller, sizeof(res) - strlen(res));
                res[strlen(res)] = '\n';
                strncat(res, list -> report.errmsg, sizeof(res) - strlen(res));
                res[strlen(res)] = '\n';
                old = list;
                list = list -> next;
                free(old);
        }
        reslen = strlen(res);
        return res;
}
