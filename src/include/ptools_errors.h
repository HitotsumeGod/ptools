/** 
 * Error handling API for peter projects.
 * 
 * ptools_errors uses C enumerations for its error handling.
 * A ptools_errors 'errorcode' is a member of an enum, denoted
 * by a short summary of its error-context, such as 
 * 'COMMON_BAD_ARGS_ERR' denoting an errorcode for an error caused 
 * by incorrect values being passed to a function. This header file
 * defines one such collection of errorcodes: the enum common_error.
 * This enum contains within it errorcodes for errors likely to occur
 * within any project utilizing a C standard library, as well as a
 * final errorcode, COMMON_PROJECT_ERROR, used to tell the error
 * handler that it has been presented with a project-specific error.
 * Speaking of those project-specific errors, what are they? A
 * project-specific errorcode relates to an error unique to a given
 * C project, as opposed to the common errors discussed before.
 * Project-specific errorcodes should be defined within the dependant
 * project, and should follow the common_error syntax, i.e. 
 * {PROJECT_NAME}_{ERROR_CONTEXT}_ERR. Since enum contents are fixed
 * at definition, there is no way to declare a generic project-error
 * enum here and allow its modification by the parent project, which
 * is why the API is how it is. 
 * When it comes to actually doing things with our errorcodes, the
 * API provides a nested-function design. Upon encountering an error,
 * a function ought make a call to ptools_handle_error(), supplying
 * the appropriate common_error errorcode (COMMON_PROJET_ERR if the
 * error is a project-specific one). If the error is a common one,
 * the remaining two arguments may be left NULL. In this case, the
 * errorcode will be easily parsed, and the function will return a
 * human-readable string providing a more detailed explanation of
 * the error-context, to be printed for a debugger's use. If a project-
 * specific error has occured, however, COMMON_PROJECT_ERR should be
 * set as the common_error, and the specific project errorcode should
 * be cast to a void pointer and passed as the second argument to 
 * ptools_handle_error(). The final argument is then a callback function
 * defined by the parent project in the format specified within this API,
 * which ptools_handle_error() will then use to parse the project-specific
 * errorcode. This callback function ought be designed in a very similar
 * way to ptools_handle_error() itself, and an example of such is included
 * within this repository, within 'examples/errorhandler.c'. 
 * As an example:
 * ------------------------------------------------------------------------------------
 * 1. Project error occurs (sample project errorcode: MYPROJECT_NONIC_ERR)
 * 2. Project calls ptools_handle_error(COMMON_PROJECT_ERROR, (void *) &MYPROJECT_NONIC_ERR, myproject_handler).
 * 3. ptools_handle_error() switches to case COMMON_PROJECT_ERROR, and so calls myproject_handler() with the void-cast MYPROJECT_NONIC_ERR.
 * 4. myproject_handler() uncasts the void pointer, and then switches to the appropriate case.
 * 5. myproject_handler() sets its result string to the descriptive error string associated with the errorcode, and returns to ptools_handle_error().
 * 6. ptools_handle_error() sets its result string to that returned by myproject_handler(), and returns to the project
 * 7. Project-defined implementation, probably printing the errorstring to stderr.
 * ------------------------------------------------------------------------------------
*/

#ifndef __PTOOLS_ERRORS_H__
#define __PTOOLS_ERRORS_H__

#define ERRMSGLIM   240

enum common_error {
        COMMON_BADARGS_ERR,
        COMMON_MALLOC_ERR,
        COMMON_SOCKET_ERR,
        COMMON_BIND_ERR,
        COMMON_SEND_ERR,
        COMMON_RECV_ERR
        COMMON_PROJECT_ERR
};

typedef char *(*project_handle_error)(void *);

extern char *ptools_handle_error(enum common_error common, void *project, project_handle_error handler);

#endif //__PTOOLS_ERRORS_H__
