#ifndef _ASSERT_MACROS_H_
#define _ASSERT_MACROS_H_

#include <iostream>

#define GRN_START       "\n\033[1;32m"
#define GRN_END         "\033[0m\n\n"
#define RED_START       "\n\033[1;31m"
#define RED_END         "\033[0m\n\n"

#define PRINT_EVAL_MSG(eval) \
{ \
        if ((eval)) \
        { \
                std::cout << GRN_START "Assert \"" << #eval << "\" passed" GRN_END; \
        } \
        else \
        { \
                std::cout << RED_START "Assert \"" << #eval << "\" failed!" RED_END; \
        } \
}

#define ASSERT_TRUE(eval) \
{ \
        PRINT_EVAL_MSG(eval); \
        if (!(eval)) \
                return -1; \
}

#endif