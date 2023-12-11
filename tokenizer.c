#include "custom_shell.h"

/**
 * custom_strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **custom_strtow(char *str, char *d)
{
    int i, j, k, m, numwords = 0;
    char **s;

    if (str == NULL || str[0] == 0)
        return (NULL);
    if (!d)
        d = " ";
    for (i = 0; str[i] != '\0'; i++)
        if (!custom_is_delim(str[i], d) && (custom_is_delim(str[i + 1], d) || !str[i + 1]))
            numwords++;

    if (numwords == 0)
        return (NULL);
    s = custom_malloc((1 + numwords) * sizeof(char *));
    if (!s)
        return (NULL);
    for (i = 0, j = 0; j < numwords; j++)
    {
        while (custom_is_delim(str[i], d))
            i++;
        k = 0;
        while (!custom_is_delim(str[i + k], d) && str[i + k])
            k++;
        s[j] = custom_malloc((k + 1) * sizeof(char));
        if (!s[j])
        {
            for (k = 0; k < j; k++)
                custom_free(s[k]);
            custom_free(s);
            return (NULL);
        }
        for (m = 0; m < k; m++)
            s[j][m] = str[i++];
        s[j][m] = 0;
    }

