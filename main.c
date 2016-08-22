#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define DEVICE_NAME "hello_device"
#define PROC_NAME "mod_hello"

const char *msg = "Hello from userspace !\n"; /* msg for writting */
char *read_buffer; /* buffer for reading */

FILE * open_file(const char *filename);
void read_file(FILE *fd);
void write_file(FILE *fd);

int main(int argc, char const *argv[]) {

    /* read/write /dev file */
    FILE *fd;

    // fd = open_file(DEVICE_NAME);
    // read_file(fd);
    // write_file(fd);
    // fclose(fd);

    /* read /proc file */
    fd = open_file(PROC_NAME);
    read_file(fd);
    fclose(fd);

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

void read_file(FILE *fd) {

    read_buffer = (char *)malloc(50 * sizeof(char));
    fgets(read_buffer, 50, fd);
    printf("Message: %s\n", read_buffer);

    free(read_buffer);
}

void write_file(FILE *fd) {
    if (fputs(msg, fd) == -1)
        fprintf(stderr, "fputs error!\n");
}
