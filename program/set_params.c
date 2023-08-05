#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define MODULE_NAME "main"
#define PARAM_NAME "timer_clock"

int main() {
    int fd;
    const char *module_name = MODULE_NAME;
    const char *param_name = PARAM_NAME;
    char *timer_clock[20]; // Replace this with the new value you want to set
    char *path[100];
    fd = open("/sys/module/main/parameters/timer_clock", O_RDONLY);
    if (fd < 0) {
        perror("Error opening the parameter file");
        exit(EXIT_FAILURE);
    }
    if (read(fd, timer_clock, sizeof(timer_clock)) < 0) {
        perror("Error reading the parameter file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    printf("Old value of the parameter timer_clock: %s\n", timer_clock);
    printf("Enter the new value for the parameter timer_clock: ");
    scanf("%s", &timer_clock);
    fd = open("/sys/module/main/parameters/path", O_RDONLY);
    if (fd < 0) {
        perror("Error opening the parameter file");
        exit(EXIT_FAILURE);
    }
    if (read(fd, path, sizeof(path)) < 0) {
        perror("Error reading the parameter file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    printf("Old value of the parameter path: %s\n", path);
    printf("Enter the new value for the parameter path: " );
    scanf("%s", &path);

    // Open the parameter file
    fd = open("/sys/module/main/parameters/timer_clock", O_WRONLY);
    if (fd < 0) {
        perror("Error opening the parameter file");
        exit(EXIT_FAILURE);
    }
    

    // Write the new value to the parameter file
    if (write(fd, timer_clock, sizeof(timer_clock)) < 0) {
        perror("Error writing to the parameter file");
        close(fd);
        exit(EXIT_FAILURE);
    }


    printf("Successfully set the parameter value to: %s\n", &timer_clock);
    close(fd);
    fd = open("/sys/module/main/parameters/path", O_WRONLY);
    if (fd < 0) {
        perror("Error opening the parameter file");
        exit(EXIT_FAILURE);
    }

    if (write(fd, path, sizeof(path)) < 0) {
        perror("Error writing to the parameter file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Successfully set the parameter value to: %s\n", &path);
    close(fd);
    
    return 0;
}
