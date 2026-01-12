/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 22:01:01 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/08 12:44:55 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int    ft_balance(char *str)
{
    int open = 0;
    int close = 0;
    int i = 0;
    while(str[i])
    {
        if(str[i] == '(')
            open++;
        else if (str[i] == ')')
        {
            if(open > 0)
                open--;
            else
                close++;
        }
        i++;
    }
    return open + close;
}

void    rip(char *str, int balance, int changes, int pos)
{
    if(balance == changes && !ft_balance(str))
    {
        puts(str);
        return ;
    }
    int	i = pos;
    while(str[i])
    {
        if(str[i] == ')' || str[i] == '(')
        {
            char temp = str[i];
            str[i] = ' ';
            rip(str, balance, changes + 1, i + 1);
            str[i] = temp;
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    int	balance = ft_balance(argv[1]);
    rip(argv[1], balance, 0, 0);
    return 0;
}
