/* 
 * File:   mPARSING.h
 * Author: User
 *
 * Created on December 7, 2024, 10:24 PM
 */

#ifndef MPARSING_H
#define	MPARSING_H

// functions used in parse function
int find_char_after(const char *str, char target, int start_pos);

//to get the speed from the string and turn it into integer
int extract_number(const char *str, int start_pos);

// parsing the data (getting the data between brackets)
uint8_t parse_mpu_data(const char *data, MotorData_t * motor_data);

#endif	/* MPARSING_H */

