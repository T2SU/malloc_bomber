#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char    *str;
    int     i;

    str = malloc(100);
    i = 0;
    while (i < 10)
    {
        str[i] = '0' + i;
        i++;
    }
    str[i] = '\0';
    write(1, str, i);
    free(str);
    write(1, "\n", 1);

    return 0;
}