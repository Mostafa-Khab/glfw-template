/*********************************
 * author     : mostafa khaled
 * date       : Sat Sep 14 02:17:56 AM EEST 2024
 * desc       : 
 ********************************/
#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define log(X) fprintf(stderr, "\033[31mERROR: %s\033[0m\n", X)

#endif /* !LOG_HPP */
