#include "custom_shell.h"

/**
 * display_environment - prints the current environment
 * @shell_info: Structure containing potential arguments. Used to maintain
 *              constant function prototype.
 * Return: Always 0
 */
int display_environment(shell_info_t *shell_info)
{
    print_custom_list_str(shell_info->env);
    return (0);
}

/**
 * get_environment_variable - gets the value of an environment variable
 * @shell_info: Structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * @name: env variable name
 *
 * Return: the value of the environment variable
 */
char *get_environment_variable(shell_info_t *shell_info, const char *name)
{
    list_t *node = shell_info->env;
    char *p;

    while (node)
    {
        p = starts_with(node->str, name);
        if (p && *p)
            return (p);
        node = node->next;
    }
    return (NULL);
}

/**
 * set_environment_variable - Initializes a new environment variable,
 *                            or modifies an existing one
 * @shell_info: Structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * Return: Always 0
 */
int set_environment_variable(shell_info_t *shell_info)
{
    if (shell_info->argc != 3)
    {
        custom_eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (custom_setenv(shell_info, shell_info->argv[1], shell_info->argv[2]))
        return (0);
    return (1);
}

/**
 * unset_environment_variable - Removes an environment variable
 * @shell_info: Structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * Return: Always 0
 */
int unset_environment_variable(shell_info_t *shell_info)
{
    int i;

    if (shell_info->argc == 1)
    {
        custom_eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= shell_info->argc; i++)
        custom_unsetenv(shell_info, shell_info->argv[i]);

    return (0);
}

/**
 * initialize_environment_list - populates the environment linked list
 * @shell_info: Structure containing potential arguments. Used to maintain
 *                constant function prototype.
 * Return: Always 0
 */
int initialize_environment_list(shell_info_t *shell_info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        custom_add_node_end(&node, environ[i], 0);
    shell_info->env = node;
    return (0);
}
