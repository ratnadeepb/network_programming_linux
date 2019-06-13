/*
 * =====================================================================================
 *
 *       Filename:  debug_macros.h
 *
 *    Description:  Debug macros
 *
 *        Version:  1.0
 *        Created:  06/13/2019 01:08:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ratnadeep Bhattacharya (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __DBG_H__
#define __DBG_H__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG // removes all debug lines
#define debug(M, ...) // because #define debug (M, ...) is replaced with nothing
#else
// print to standard error
// __FILE__ --> current file
// __LINE__ --> current line
#define debug(M, ...) fprintf(stderr, "DEBUG: %s:%d: " M "\n",\
                __FILE__, __LINE__, ##__VA_ARGS__)
#endif // NDEBUG

// readable form of error
#define clean_errno()(errno == 0 ? "None" : strerror(errno))

// log error, warning, info
#define log_error(M, ...) fprintf(stderr, \
                "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__,\
                clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, \
                "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__,\
                clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, \
                "[INFO] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__,\
                clean_errno(), ##__VA_ARGS__)

// log the error; then jump to error to clean up
#define check(A, M, ...) if(!(A)) {\
        log_error(M, ##__VA_ARGS__); errno = 0; goto error; }

// place sentinel in parts of a function which shouldn't run
// if it does then control jumps to error
// and logs an error
#define sentinel(M, ...) { log_error(M, ##__VA_ARGS__);\
        errno = 0; goto error; }

// check if a pointer is valid
#define check_mem(A) check((A), "out of memory")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__);\
        errno = 0; goto error; }

#endif // __DBG_H__
