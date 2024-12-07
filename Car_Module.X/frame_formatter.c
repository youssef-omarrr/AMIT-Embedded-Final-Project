
// Utility function to format and send angle data over UART for Debugging
static void sendAngleData(const AngleState* state) {
    char buffer[30];
    sprintf(buffer, "X Angle: %.2f\tY Angle: %.2f\tZ Angle: %.2f\r\n",
        state->angles[X],
        state->angles[Y],
        state->angles[Z]);
    uart_send_str(buffer);
}

// main Formmating function to send the data in the format
// <(direction)(speed)> 
// direction:W,A,S,D Speed:0-255

void formatSignalMsg(const AngleState* state, char* frame) {
    char direction;
    char speed_str[4]; // Enough to hold "255" + null terminator
    int speed;
    float absX = fabs(state->angles[X]);
    float absY = fabs(state->angles[Y]);

    // Determine primary direction based on largest angle
    if (absX > absY) {
        direction = (state->angles[X] > 0) ? 'W' : 'S'; // Forward/Backward
        speed = (int) ((absX * 255) / 90.0);
    } else {
        direction = (state->angles[Y] > 0) ? 'D' : 'A'; // Right/Left
        speed = (int) ((absY * 255) / 90.0);
    }

    // Clamp speed to the range [0, 255]
    if (speed > 255) speed = 255;
    if (speed < 0) speed = 0;

    // Manually construct the frame string
    int i = 0;

    // Add "<("
    frame[i++] = '<';
    frame[i++] = '(';

    // Add direction
    frame[i++] = direction;

    // Add ")("
    frame[i++] = ')';
    frame[i++] = '(';

    // Convert speed to string manually
    int temp_speed = speed;
    int digits = 0;
    do {
        digits++;
        temp_speed /= 10;
    } while (temp_speed > 0);

    for (int j = digits - 1; j >= 0; j--) {
        speed_str[j] = (speed % 10) + '0';
        speed /= 10;
    }
    speed_str[digits] = '\0'; // Null-terminate the string

    // Append speed to the frame
    for (int j = 0; speed_str[j] != '\0'; j++) {
        frame[i++] = speed_str[j];
    }

    // Add ")>"
    frame[i++] = ')';
    frame[i++] = '>';

    // Null-terminate the frame string
    frame[i] = '\0';
}
