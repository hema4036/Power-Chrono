#include"types.h"

#ifndef CHECK_VALID_H
#define CHECK_VALID_H

/*
 * Validation Functions for RTC / Time / Date
 * Each function returns:
 *   1 ? valid
 *   0 ? invalid
 */

// Time validation
int check_hour(u32);
int check_minute(u32);
int check_second(u32);

//day validation
int check_day(u32);

//date valudation
int check_date(u32,u32,u32);
int check_month(u32,u32,u32*);
int check_year(u32,u32,u32*);

#endif //CHECK_VALID_H
