/** 
 * Error handling API for peter projects.
 * 
 * The API works as follows:
 * A broad enumeration is located in this header file, containing generic
 * errors that are common to come across in all C programs. The implementating
 * project, then, is responsible for designing a similar enum for project-
 * specific errors, and for implementing an error-handling function similar to
 * our provided example ('std/examples/errorhandler.c')
*/

#ifndef __PTOOLS_ERRORS_H__
#define __PTOOLS_ERRORS_H__

enum common_error {
        COMMON_BAD_ARGS_ERR,
        COMMON_MALLOC_ERR,
}

#endif //__PTOOLS_ERRORS_H__
