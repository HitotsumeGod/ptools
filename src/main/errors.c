#include "ptools.h"
#include <string.h>

char *ptools_report_errors(struct errep *list)
{
        static char res[ERRMSGMAX * 10];
        static int reslen = 0;
        struct errep *old;

        for (int i = 0; i < reslen; i++)
                res[i] = 0;
        while (list) {
                strncat(res, list -> caller, sizeof(res) - strlen(res));
                res[strlen(res)] = '\n';
                strncat(res, list -> msg, sizeof(res) - strlen(res));
                res[strlen(res)] = '\n';
                old = list;
                list = list -> next;
                free(old);
        }
        reslen = strlen(res);
        return res;
}
