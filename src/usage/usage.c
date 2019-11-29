/*
** EPITECH PROJECT, 2019
** my_screensaver
** File description:
** usage function
*/

#include <unistd.h>
#include <fcntl.h>
#include "my.h"

int usage(int exit_value, char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    char buffer[433];
    int size = read(fd, buffer, 433);

    buffer[433] = '\0';
    close(fd);
    if (size <= 0)
        return 84;
    write(1, buffer, my_strlen(buffer));
    return exit_value;
}

int invalid_arg_nbr(int exit_value, int argc, char *binary_name)
{
    my_put_error_str(binary_name);
    my_put_error_str(": bad arguments: ");
    my_put_error_str(my_nbr_get_str(argc - 1));
    my_put_error_str(" given but 1 is required\nretry with -h\n");
    return exit_value;
}