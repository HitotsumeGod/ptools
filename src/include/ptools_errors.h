/** 
 * Error handling API for peter projects.
 * 
 * ptools_errors uses C enumerations for its error handling.
 * A ptools_errors 'errorcode' is a member of an enum, denoted
 * by a short summary of its error-context, such as 
 * 'COMMON_BADARGS_ERR' denoting an errorcode for an error caused 
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
 *
 * Easily the most useful tool in program debugging is the backtrace,
 * which supplies the debugger with a chronological sequence of error
 * events, making it far easier to determine where a particular bug
 * occurred and how it might be resolved. In the effort of
 * incorporating this essentially tool into the fabric of ptools' error
 * handling, the struct errmsg was designed. errmsg structs are designed
 * to be individual entries in a linked list, which, you may notice, is the
 * natural representation of a chronological collection, useful for backtracing.
 * In properly implementing ptools' error handling, EVERY SINGLE function
 * designed by the dependent project ought return a pointer to a struct errmsg;
 * this is the entry point to a linked list, as mentioned before, which allows
 * functions to collect errorcodes and messages occuring within nested functions,
 * and return them in a coherent form for processing. This processing, then, is
 * handled via the ptools_handle_error() function, which takes as its arguments
 * a struct errmsg pointer (the linked list) and a project_handle_error callback,
 * whose implementation is reliant upon the dependant project. A prototype is provided
 * in /examples/errorhandler.c. This callback need provide only a single service: the
 * translation of project-specific errcodes into robust, detailed error messages.
 * To illustrate all of these parts at work, the following example is provided:
 * ----------------------------------------------------------------------------
 * 1. main() calls the function do_big_thing().
 * 2. do_big_thing() calls the function do_small_thing().
 * 3. do_small_thing() encounters an error. It thus builds a struct errmsg, with
 *        errcode.common_err = COMMON_PROJECT_ERR and errcode.project_err = 
 *        PROJECT_EXAMPLE_ERR. It then sets function_name to do_small_thing()
 *        and null-terminates its next field, finally returning the errmsg.
 * 4. do_big_thing(), upon realizing that do_small_thing() encountered an error
 *        (which it realizes by checking the errmsg's errcode.common_err for
 *        COMMON_SUCCESS_ERR), constructs a struct errmsg in much the same way
 *        as Step 3, besides setting its errcode.project_err to something along
 *        the lines of PROJECT_DOSMALLTHING_ERR, thus providing what information
 *        it knows and allowing do_small_thing() itself to elucidate the situation
 *        with its own errmsg, AND attaching itself to the end of do_small_thing()'s 
 *        errmsg, thus starting a linked list that crucially begins at the point
 *        of error FURTHEST from the original caller (main()). It then returns
 *        the errmsg list.
 * 5. main(), upon realizing that do_big_thing() encountered an error, passes
 *        the entire errmsg list, which in C is beautifully encapsulated into a
 *        single struct pointer, to ptools_handle_error().
 * 6. ptools_handle_error() then iterates over each item in the linked list, and either:
 *        - translates the errorcode to an errormsg in-function, if the code is a COMMON one
 *        - retrieves an errormsg via a call to the project-implemented handler, passing
 *                  the errmsg's errcode.project_err.
 *        each errormsg is added to a single large string, which is then finally passed
 *        back to main() to be printed to stderr, written to a log file, etc, etc.
 * ------------------------------------------------------------------------------
*/

#ifndef __PTOOLS_ERRORS_H__
#define __PTOOLS_ERRORS_H__

#define ERRMSGMAX       2400
#define FUNCNAMEMAX     40

#define FILL_ERREP(rep, caller, msg)                                    \
        if ((rep = malloc(sizeof(struct errep))) == NULL)               \
        rep -> caller = caller;                                         \
        rep -> msg = msg;                                               \
        rep -> next = NULL;                                             

//short for 'error_report'
struct errep {
        char *caller;
        char *msg;
        struct errep *next;
};

extern char *ptools_format_errors(struct errep *linked_list);

#endif //__PTOOLS_ERRORS_H__
