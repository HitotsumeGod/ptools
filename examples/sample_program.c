#include "ptools.h"
#include <stdio.h>
#include <stdlib.h>

enum project_enum {
        ERR_1,
        ERR_2,
        ERR_3
};

char *sample_handler(void *errcode);
struct errmsg *tempfunc_top(void);
struct errmsg *tempfunc_one(void);
struct errmsg *tempfunc_two(void);
struct errmsg *tempfunc_three(void);

int main(void)
{
        struct errmsg *res;

        res = tempfunc_two();
        printf("%s\n", ptools_handle_error(res, sample_handler));
        return 0;
}

char *sample_handler(void *spec)
{
        enum project_enum ex;
        char *errstr;
        
        ex = *((enum project_enum *) spec);
        switch (ex) {
        case ERR_1:
                errstr = "Error number one has occured";
                break;
        case ERR_2:
                errstr = "Error number two has occured";
                break;
        case ERR_3:
                errstr = "Error number three has occured";
                break;
        default:
                errstr = "sample_handler() was passed an improper error enum";
        }
        return errstr;
}

struct errmsg *tempfunc_top(void)
{
        struct errmsg *res;

        res = malloc(sizeof(struct errmsg));
        res -> errcode.common_err = COMMON_SUCCESS_ERR;
        res -> errcode.project_err = NULL;
        res -> function_name = "tempfunc_top()";
        res -> next = tempfunc_one();
        res -> next -> next = tempfunc_two();
        res -> next -> next -> next = tempfunc_three();
        return res;
}

struct errmsg *tempfunc_one(void)
{
        struct errmsg *res;

        res = malloc(sizeof(struct errmsg));
        res -> errcode.common_err = COMMON_BADARGS_ERR;
        res -> errcode.project_err = NULL;
        res -> function_name = "tempfunc_one()";
        res -> next = NULL;
        return res;
}

struct errmsg *tempfunc_two(void)
{
        struct errmsg *res;
        enum project_enum num = ERR_1;

        res = malloc(sizeof(struct errmsg));
        res -> errcode.common_err = COMMON_PROJECT_ERR;
        res -> errcode.project_err = &num;
        res -> function_name = "tempfunc_two()";
        res -> next = NULL;
        return res;
}

struct errmsg *tempfunc_three(void)
{
        struct errmsg *res;
        enum project_enum num = ERR_3;

        res = malloc(sizeof(struct errmsg));
        res -> errcode.common_err = COMMON_PROJECT_ERR;
        res -> errcode.project_err = &num;
        res -> function_name = "tempfunc_three()";
        res -> next = NULL;
        return res;
}