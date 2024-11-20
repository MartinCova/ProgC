#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int main() {
    int serial_port;
    struct termios tty;

    // Open the serial port
    serial_port = open("/dev/ttyS1", O_RDWR | O_NOCTTY);
    if (serial_port < 0) {
        perror("Error opening serial port");
        return 1;
    }

    // Configure the serial port
    if (tcgetattr(serial_port, &tty) != 0) {
        perror("Error getting serial port attributes");
        return 1;
    }

    // Set baud rate
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    // Set data size and parity
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;    // 8-bit data
    tty.c_cflag &= ~PARENB;                        // No parity
    tty.c_cflag &= ~CSTOPB;                        // 1 stop bit

    // Disable hardware flow control
    tty.c_cflag &= ~CRTSCTS;

    // Enable receiver and ignore control lines
    tty.c_cflag |= CREAD | CLOCAL;

    // Set raw input mode
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    // Set raw output mode
    tty.c_oflag &= ~OPOST;

    // Set timeout between characters
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 10;

    // Apply the settings to the serial port
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        perror("Error setting serial port attributes");
        return 1;
    }

    // Read and write data
    char buffer_write[256];
    char buffer_read[256];
    char received_byte;
    ssize_t num_bytes;

    // Read data from serial port
    int i;
    num_bytes = read(serial_port, received_byte, sizeof(received_byte));
    while(received_byte != "\r"){
        ==i = i+1;
        buffer_read[i] = received_byte;
        num_bytes = read(serial_port, received_byte, sizeof(received_byte));
    }

    if (num_bytes < 0) {
        perror("Error reading from serial port");
        return 1;
    }

    // Write data to serial port
    num_bytes = write(serial_port, buffer_write, num_bytes);
    if (num_bytes < 0) {
        perror("Error writing to serial port");
        return 1;
    }

    // Close the serial port
    close(serial_port);

    return 0;
}