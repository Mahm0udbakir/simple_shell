#include "custom_shell.h"

/**
 * check_interactive_mode - determines if the shell is in interactive mode
 * @shell_info: custom structure containing shell information
 *
 * Returns: 1 if the shell is in interactive mode, 0 otherwise
 */
int check_interactive_mode(shell_info_t *shell_info)
{
    return (isatty(STDIN_FILENO) && shell_info->input_fd <= 2);
}

/**
 * is_separator - checks if a character is a separator
 * @ch: the character to check
 * @separators: the separator string
 * Return: 1 if true, 0 if false
 */
int is_separator(char ch, char *separators)
{
    while (*separators)
        if (*separators++ == ch)
            return (1);
    return (0);
}

/**
 * custom_is_alpha - checks for alphabetic character
 * @ch: The character to check
 * Return: 1 if ch is alphabetic, 0 otherwise
 */
int custom_is_alpha(int ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return (1);
    else
        return (0);
}

/**
 * custom_atoi - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int custom_atoi(char *str)
{
    int index, sign = 1, flag = 0, result;
    unsigned int num_result = 0;

    for (index = 0;  str[index] != '\0' && flag != 2; index++)
    {
        if (str[index] == '-')
            sign *= -1;

        if (str[index] >= '0' && str[index] <= '9')
        {
            flag = 1;
            num_result *= 10;
            num_result += (str[index] - '0');
        }
        else if (flag == 1)
            flag = 2;
    }

    result = (sign == -1) ? -num_result : num_result;
    return (result);
}

