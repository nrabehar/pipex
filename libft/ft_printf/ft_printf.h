/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:14:53 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/01 14:59:29 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_flags
{
	int		minus;
	int		plus;
	int		hash;
	int		dot;
	int		dot_value;
	int		space;
	int		width;
	int		zero;
}			t_flags;

typedef struct s_storage
{
	int		cont_length;
	char	*content;
	char	*flags;
	char	format;
	int		is_null;
}			t_storage;

/* Core */
int			ft_printf(char const *format, ...);
int			ft_printf_fd(int fd, char const *format, ...);
void		ft_pf_parse_value(va_list args, char const *format, char **content);
/* Printer */
void		ft_pf_putc(va_list args, t_flags *flag, t_storage *st,
				char **content);
void		ft_pf_puthex(va_list args, t_flags *flag, t_storage *st,
				char **content);
void		ft_pf_putptr(va_list args, t_flags *flag, t_storage *st,
				char **content);
void		ft_pf_putn(va_list args, t_flags *flag, t_storage *st,
				char **content);
void		ft_pf_putu(va_list args, t_flags *flag, t_storage *st,
				char **content);
void		ft_pf_puts(va_list args, t_flags *flag, t_storage *st,
				char **content);
void		ft_pf_putzu(va_list args, t_flags *flag, t_storage *st,
				char **content);
/* Flags */
int			ft_pf_is_format(int c);
int			ft_pf_is_flag(int c);
int			ft_pf_is_num_flag(int c);
int			ft_pf_is_in_flags(int c);
int			ft_pf_parse_format_flag(char const *str, t_storage *st, int start);
/* Flag utils */
char		*ft_pf_get_flags(char const *str);
void		ft_parse_flags(t_flags *flag, t_storage *st, int i);
size_t		ft_pfget_flags_size(char const *str);
/* Numbers Manipulation */
size_t		ft_pf_get_num_len(unsigned long int num, int base_length);
int			ft_isdigit(int c);
char		*ft_pf_ltoa(long num);
char		*ft_pf_utoa(unsigned long num);
char		*ft_pf_hextoa(unsigned long int num);
/* Hex */
char		*ft_pf_get_hex_content(unsigned int n, t_flags *flag);
void		ft_pf_join_hex(const char *hex_content, int is_upper,
				char **content);
/* Utils */
char		*ft_pfswitch_case(char *str);
void		*ft_calloc(size_t nmemb, size_t size);

/* storage */
void		ft_pfjoin_padding(int size, const int c, char **content);
void		ft_pf_join_content(char **content, char *to_join);

#endif