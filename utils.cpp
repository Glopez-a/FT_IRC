/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:22:07 by isfernan          #+#    #+#             */
/*   Updated: 2021/11/18 18:41:11 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

bool	find_command(std::string command, std::list<std::string> commands)
{
	typedef std::list<std::string>::iterator it_list;

	it_list start = commands.begin();
	it_list end = commands.end();

	for (; start != end ; ++start)
		if (*start == command)
			return (true);
	return (false);
}

int		ft_max(int a , int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

static int		ft_atoi(const char *str)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb);
}


int		get_port(char *str)
{
	int ret;

	if (ft_strlen(str) > 10)
	{
		std::cout << "Port rank not valid; default port (6667) will be used instead\n";
		return (6667);
	}
	else
	{
		ret = ft_atoi(str);
		if (ret < 1 || ret > 65535)
		{
			std::cout << "Port rank not valid; default port (6667) will be used instead\n";
			return (6667);
		}
		return (ret);
	}
}


char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}


int		ft_isalpha(int c)
{
	if (65 <= c && c <= 90)
		return (1);
	else if (97 <= c && c <= 122)
		return (1);
	else
		return (0);
}

int		ft_isalnum(int c)
{
	if (65 <= c && c <= 90)
		return (1);
	else if (97 <= c && c <= 122)
		return (1);
	else if (48 <= c && c <= 57)
		return (1);
	else
		return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

bool	ft_isspecial(char c)
{
	if (c != '[' && c != ']'
		&&  c != '\\' &&  c != '`' && c != '_'
		&& c != '^' && c != '{' && c !='|' && c != '}')
		return (false);
	return (true);
}

char	*ft_substr(char const *s, char c)
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != c)
		i++;
	len = i;
	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

uint64_t	getTime(void)
{
	static struct timeval	end;

	gettimeofday(&end, NULL);
	return ((end.tv_sec * (uint64_t)1000) + (end.tv_usec / 1000));
}


void displayLog(std::string const & log, std::string const & cmd , User *usr )
{
	displayTimestamp();
	std::cout << " : "<< std::setfill('.')  << std::setw(30) << log.substr(0,25);
	std::cout << " IP: " <<  usr->getIp();
	std::cout << " Socket: " << usr->getsockfd();
	std::cout << cmd << std::endl;
}


void displayTimestamp( void )
{
	time_t now = time(0);

	tm ltm = *localtime(&now);
	std::cout << GREEN"" << std::setfill('0') << "[" << (ltm.tm_year + 1900)
			  << std::setw(2) << ltm.tm_mon + 1
			  << std::setw(2) << ltm.tm_mday << "_"
			  << std::setw(2) << ltm.tm_hour
			  << std::setw(2) << ltm.tm_min
			  << std::setw(2) << ltm.tm_sec << "] "WHITE;
}

std::string		ft_toupper(std::string str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	return (str);
}
