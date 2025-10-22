#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

char	**ft_split(char *str);

int		count_words(char *str)
{
	int	word_counter = 0;
	int	in_word = 0;
	int i = 0;

	while(str[i] == ' ')
	{
		i++;
	}
	while(str[i] != '\0')
	{
		while((str[i] >= 33) && (str[i] <= 126))
		{
			if(in_word == 0)
			{
				word_counter++;
			}
			in_word = 1;
			i++;
		}
		while(str[i] == ' ')
		{
			in_word = 0;
			i++;
		}
	}
	return(word_counter);
}

char	**ft_split(char *str)
{
	char	**big_boss;
	int		word_counter = count_words(str);
	int		size_for_malloc = 0;
	int		index_array = 0;

	big_boss = malloc(sizeof(char*) * (word_counter + 1));	// Alloc des pointeurs seulement

	int i = 0;
	while(str[i] != '\0')
	{
		while(str[i] == ' ')
		{
			i++;
		}
		while((str[i] >= 33) && (str[i] <= 126))
		{
			size_for_malloc++;
			i++;
		}
		if(index_array < word_counter)
		{
			big_boss[index_array] = malloc(sizeof(char) * (size_for_malloc + 1));
			index_array++;
			size_for_malloc = 0;
		}
	}

	i = 0;
	index_array = 0;
	int sub_index_array = 0;

	while(str[i] != '\0')
	{
		while(str[i] == ' ')
		{
			i++;
		}
		while((str[i] >= 33) && (str[i] <= 126))
		{
			big_boss[index_array][sub_index_array] = str[i];
			sub_index_array++;
			i++;
		}
		if(index_array < word_counter)
		{
			big_boss[index_array][sub_index_array] = '\0';
			index_array++;
			sub_index_array = 0;
		}
	}
	big_boss[word_counter] = NULL;
	return(big_boss);
}

int		main(void)
{
	char	*str = "  This Test    ";
	char	**big_boss;
	big_boss = ft_split(str);

	int i = 0;
	while(big_boss[i] != NULL)
	{
		printf("Big_Boss[%d] = %s\n", i, big_boss[i]);
		i++;
	}

	i = 0;

	while(big_boss[i] != NULL)
	{
		free(big_boss[i]);
		i++;
	}
	free(big_boss);
	return(0);
}

