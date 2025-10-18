#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

/*
Converts the string argument str (base N <= 16) to an integer (base 10) and returns it.

The characters recognized in the input are: 0123456789abcdef
Those are, of course, to be trimmed according to the requested base. For
example, base 4 recognizes "0123" and base 16 recognizes "0123456789abcdef".

Uppercase letters must also be recognized: "12fdb3" is the same as "12FDB3".

Minus signs ('-') are interpreted only if they are the first character of the
string.
*/


int		ft_atoi_base(const char *str, int str_base)
{
	// later - convertir la str en lowercase pour traiter les 2 cas
	// later - deal with menus sign

	char	*string_max = "0123456789abcdef";		// Biggest base = 16
	char	char_options[str_base + 1];				// Null term

	int i = 0;
	while(i < str_base)
	{
		char_options[i] = string_max[i];
		i++;
	}
	char_options[i] = '\0';

	i = 0;
	int j = 0;
	int pin_index = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (char_options[j] != '\0')
		{
			if(str[i] == char_options[j])
			{
				pin_index = pin_index * str_base + j;			// 0 * 16 + 13 // 13 * 16 + 6
				pin_index |= j;
			}
			j++;
		}
		i++;
	}
	return(pin_index);
}

int		main(void)
{
	const char	*str2 = "d6";
	int			base = 16;

	printf("%d\n", ft_atoi_base(str2, base));

	return(0);
}
