/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:10:18 by krios-fu          #+#    #+#             */
/*   Updated: 2021/11/11 18:23:06 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User( std::string const & nick )
	: _nick(nick)
{

}

User::~User()
{

}


std::string const & User::getBufferCmd() const { return this->_buffer_cmd; }

void	User::setBufferCmd( std::string const & buffer_cmd )
{
	this->_buffer_cmd = buffer_cmd;
}

std::string const & User::getNick() const
{
	return this->_nick;
}