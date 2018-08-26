#ifndef _ASSERT_MACROS_H_
#define _ASSERT_MACROS_H_

#include <iostream>

#define GRN_START       "\n\033[1;32m"
#define RED_START       "\n\033[1;31m"
#define FMT_END         "\033[0m\n\n"

#define PRINT_EVAL_MSG(eval) \
{ \
        if ((eval)) \
        { \
                printf(GRN_START "%s, %d: Assert \" %s \" passed" FMT_END, __FILE__, __LINE__, #eval); \
        } \
        else \
        { \
                printf(RED_START "%s, %d: Assert \" %s \" failed!" FMT_END, __FILE__, __LINE__, #eval); \
        } \
}

#define ASSERT_TRUE(eval) \
{ \
        PRINT_EVAL_MSG(eval); \
        if (!(eval)) \
                return -1; \
}

#endif