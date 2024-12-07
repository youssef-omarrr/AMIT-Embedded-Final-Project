/////////////////////////////////////////////////////////
//////////--------- Parsing Functions ---------//////////
/////////////////////////////////////////////////////////

#include "mPARSING.h"

// functions used in parse function
int find_char_after(const char *str, char target, int start_pos) {
    int i = start_pos;
    while (str[i] != '\0') {
        if (str[i] == target) {
            return i;
        }
        i++;
    }
    return -1;
}

//to get the speed from the string and turn it into integer
int extract_number(const char *str, int start_pos) {
    int result = 0;
    int i = start_pos;

    //loop until a number is found
    while (str[i] != '\0' && (str[i] < '0' || str[i] > '9')) {
        i++;
    }

    // turn the number to an integer
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}

// parsing the data (getting the data between brackets)
uint8_t parse_mpu_data(const char *data, MotorData_t * motor_data) {
    if (!data || !motor_data) return 0;

    int dir_start = find_char_after(data, '(', 0); //after the first '(' lies the dir
    if (dir_start >= 0) {// error handling
        char direction = data[dir_start + 1];

        int speed_pos = find_char_after(data, '(', dir_start + 1); // after the second '('
        if (speed_pos >= 0) {// error handling
            int speed = extract_number(data, speed_pos + 1);

            if (direction == 'W' || direction == 'S' ||
                    direction == 'A' || direction == 'D') { // bt2aked en ely wasal 7aga mn wasd

                //el speed mapped hena ha
                if (speed < 30) speed = 0;
                if (speed > 255) speed = 255;

                motor_data->direction = direction;
                motor_data->speed = (uint8_t) speed;
                return 1;
            }
        }
    }
    return 0;
}

/////////////////////////////////////////////////////////
//////////--------- Parsing Functions ---------//////////
/////////////////////////////////////////////////////////
