#include "custom_shell.h"

/**
 * exit_shell - exits the shell
 * @shell_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Exits with a given exit status (0) if shell_info->argv[0] != "exit"
 */
int exit_shell(shell_info_t *shell_info)
{
	int exit_status;

	if (shell_info->argv[1])  /* If there is an exit argument */
	{
		exit_status = custom_atoi(shell_info->argv[1]);
		if (exit_status == -1)
		{
			shell_info->status = 2;
			print_custom_error(shell_info, "Illegal number: ");
			custom_puts(shell_info->argv[1]);
			custom_putchar('\n');
			return (1);
		}
		shell_info->err_code = custom_atoi(shell_info->argv[1]);
		return (-2);
	}
	shell_info->err_code = -1;
	return (-2);
}

/**
 * change_directory - changes the current directory of the process
 * @shell_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int change_directory(shell_info_t *shell_info)
{
	char *current_dir, *new_dir, buffer[1024];
	int chdir_result;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		custom_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!shell_info->argv[1])
	{
		new_dir = custom_getenv(shell_info, "HOME=");
		if (!new_dir)
			chdir_result = /* TODO: what should this be? */
				chdir((new_dir = custom_getenv(shell_info, "PWD=")) ? new_dir : "/");
		else
			chdir_result = chdir(new_dir);
	}
	else if (custom_strcmp(shell_info->argv[1], "-") == 0)
	{
		if (!custom_getenv(shell_info, "OLDPWD="))
		{
			custom_puts(current_dir);
			custom_putchar('\n');
			return (1);
		}
		custom_puts(custom_getenv(shell_info, "OLDPWD=")), custom_putchar('\n');
		chdir_result = /* TODO: what should this be? */
			chdir((new_dir = custom_getenv(shell_info, "OLDPWD=")) ? new_dir : "/");
	}
	else
		chdir_result = chdir(shell_info->argv[1]);

	if (chdir_result == -1)
	{
		print_custom_error(shell_info, "can't cd to ");
		custom_eputs(shell_info->argv[1]), custom_eputchar('\n');
	}
	else
	{
		custom_setenv(shell_info, "OLDPWD", custom_getenv(shell_info, "PWD="));
		custom_setenv(shell_info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * display_help - displays help information for the shell
 * @shell_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int display_help(shell_info_t *shell_info)
{
	char **arg_array;

	arg_array = shell_info->argv;
	custom_puts("Help function call works. Function not yet implemented \n");
	if (0)
		custom_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
