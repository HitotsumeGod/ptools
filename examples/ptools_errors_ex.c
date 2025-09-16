#include "ptools.h"

struct errep *tempfunc_top(void);
struct errep *tempfunc_one(void);
struct errep *tempfunc_two(void);
struct errep *tempfunc_three(void);

int main(void)
{
        printf("%s", ptools_format_errors(tempfunc_top()));
        return 0;
}

struct errep *tempfunc_top(void)
{
        struct errep *res;

        res = tempfunc_one();
        res -> next = tempfunc_two();
        res -> next -> next = tempfunc_three();
        FILL_ERREP(res -> next -> next -> next, "tempfunc_top()", ERREP_SUCCESS);
        if (!res -> next -> next -> next) {
                fprintf(stderr, "%s\n", FILL_ERREP_ERR);
                return NULL;
        }
        return res;
}

struct errep *tempfunc_one(void)
{
        struct errep *res;

        FILL_ERREP(res, "tempfunc_one()", "sample tempfunc err");
        if (!res) {
                fprintf(stderr, "%s\n", FILL_ERREP_ERR);
                return NULL;
        }
        return res;
}

struct errep *tempfunc_two(void)
{
        struct errep *res;

        FILL_ERREP(res, "tempfunc_two()", "sample tempfunc err");
        if (!res) {
                fprintf(stderr, "%s\n", FILL_ERREP_ERR);
                return NULL;
        }
        return res;
}

struct errep *tempfunc_three(void)
{
        struct errep *res;

        FILL_ERREP(res, "tempfunc_three()", "sample tempfunc err");
        if (!res) {
                fprintf(stderr, "%s\n", FILL_ERREP_ERR);
                return NULL;
        }
        return res;
}
