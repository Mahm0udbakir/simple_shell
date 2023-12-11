#include "custom_shell.h"

/**
 * custom_main - The main entry point of the custom shell program.
 * @custom_argc: The number of command-line arguments.
 * @custom_argv: An array containing the command-line arguments.
 *
 * Return: 0 on success, 1 on error.
 */
int custom_main(int custom_argc, char **custom_argv)
{
    info_t custom_info[] = { INFO_INIT };
    int custom_fd = 2; // Default file descriptor for input (stderr).

    asm ("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (custom_fd)
        : "r" (custom_fd));

    if (custom_argc == 2)
    {
        custom_fd = custom_open(custom_argv[1], O_RDONLY);
        if (custom_fd == -1)
        {
            if (custom_errno == EACCES)
                custom_exit(126);
            if (custom_errno == ENOENT)
            {
                custom_eputs(custom_argv[0]);
                custom_eputs(": 0: Can't open ");
                custom_eputs(custom_argv[1]);
                custom_eputchar('\n');
                custom_eputchar(BUF_FLUSH);
                custom_exit(127);
            }
            return (EXIT_FAILURE);
        }
        custom_info->readfd = custom_fd;
    }

    custom_populate_env_list(custom_info);
    custom_read_history(custom_info);
    custom_hsh(custom_info, custom_argv);
    return (EXIT_SUCCESS);
}
