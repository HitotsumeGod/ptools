#include "ptools_errors.h"

enum project_enum {
        ERR1,
        ERR2,
        ERR3
};

char *sampleproject_handle_error(void *spec)
{
        enum project_enum ex;
        char *errstr;
        
        ex = *((enum project_enum *) spec);
        switch (ex) {
        case ERR1:
                errstr = "Error number one has occured";
                break;
        case ERR2:
                errstr = "Error number two has occured";
                break;
        case ERR3:
                errstr = "Error number three has occured";
                break;
        default:
                errstr = "sampleproject_handle_error() was passed an improper error enum";
        }
        return errstr;
}