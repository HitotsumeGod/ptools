#include "ptools.h"
#include <stdio.h>
#include <stdlib.h>

struct errep *tempfunc_top(void);

int main(void)
{
        struct errep *res;

        res = tempfunc_top();
        printf("%s", ptools_handle_error(res));
        return 0;
}

struct errep *tempfunc_top(void)
{
        
}