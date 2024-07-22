/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:25:54 by bryaloo           #+#    #+#             */
/*   Updated: 2024/07/22 21:29:13 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//print_char
int	print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

//print_hex
int	hex_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	put_hex(unsigned int num, const char type)
{
	if (num >= 16)
	{
		put_hex(num / 16, type);
		put_hex(num % 16, type);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (type == 'x')
				ft_putchar_fd((num - 10 + 'a'), 1);
			if (type == 'X')
				ft_putchar_fd((num - 10 + 'A'), 1);
		}
	}
}

int	print_hex(unsigned int num, const char type)
{
	if (num == 0)
		return (write(1, "0", 1));
	else
		put_hex(num, type);
	return (hex_len(num));
}

//print_nbr
int	print_nbr(int n)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(n);
	len = print_str(num);
	free(num);
	return (len);
}

//print_percent
int	print_percent(void)
{
	write(1, "%", 1);
	return (1);
}

//print_ptr
int	ptr_len(uintptr_t num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	put_ptr(uintptr_t num)
{
	if (num >= 16)
	{
		put_ptr(num / 16);
		put_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
			ft_putchar_fd((num - 10 + 'a'), 1);
	}
}

int	print_ptr(unsigned long long ptr)
{
	int	print_len;

	print_len = 0;
	print_len += write(1, "0x", 2);
	if (ptr == 0)
		print_len += write(1, "0", 1);
	else
	{
		put_ptr(ptr);
		print_len += ptr_len(ptr);
	}
	return (print_len);
}

//print_str
void	put_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	print_str(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		put_str("(null)");
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

//print_unsigned
int	num_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

char	*unsigned_itoa(unsigned int n)
{
	char	*num;
	int		len;

	len = num_len(n);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (0);
	num[len] = '\0';
	while (n != 0)
	{
		num[len - 1] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	return (num);
}

int	print_unsigned(unsigned int n)
{
	int		print_len;
	char	*num;

	print_len = 0;
	if (n == 0)
		print_len += write(1, "0", 1);
	else
	{
		num = unsigned_itoa(n);
		print_len += print_str(num);
		free(num);
	}
	return (print_len);
}
