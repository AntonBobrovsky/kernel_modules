#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define DEVICE_NAME "hello_device"

const char *msg = "Hello from userspace !\n"; /* msg for writting */
char *read_buffer; /* buffer for reading */

FILE * open_file(const char *filename); /* open file */
void read_dev(FILE *fd); /* read from /dev/ */
void write_dev(FILE *fd); /* write to /dev/ */

int main(int argc, char const *argv[]) {

    FILE *fd;

    fd = open_file(DEVICE_NAME);
    read_dev(fd);
    write_dev(fd);

    return 0;
}

FILE * open_file(const char *filename) {
    FILE *fd;

    fd = fopen("/dev/hello_device", "rw");
    if (fd < 0) {
        fprintf (stderr, "fopen: Cannot open file\n");
		exit (-1);
	}
    return fd;
}

void read_dev(FILE *fd) {

    read_buffer = (char *)malloc(50 * sizeof(char));
    fgets(read_buffer, 50, fd);
    printf("Message: %s\n", read_buffer);

    free(read_buffer);
}

void write_dev(FILE *fd) {
    if (fputs(msg, fd) == -1)
        fprintf(stderr, "fputs error!\n");
}
