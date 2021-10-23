/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:49:25 by isfernan          #+#    #+#             */
/*   Updated: 2021/10/23 15:52:10 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

// Constructor && destructor

Channel::Channel(std::string name, User *user): _name(name), _users(), _operators()
{
	this->_maxusers = MAX_USERS;
	this->_isfull = false;
	this->_operators.push_back(user);
}

Channel::~Channel() {  }

// Getters

std::string Channel::getName() const { return(this->_name); }

std::list<User *> Channel::getUsers() const
{
	return (this->_users);
}

bool	Channel::getIsFull() const { return(this->_isfull); }

bool	Channel::isOp(User * user)
{
	for (std::list<User *>::iterator it = this->_operators.begin(); it != this->_operators.end(); it++)
	{
		if ((*it)->getNick() == user->getNick())
			return (true);
	}
	return (false);
}

std::string	Channel::userList()
{
	std::string	s;

	s.assign("list of users: ");
	for (std::list<User*>::iterator it = this->_users.begin(); it != _users.end(); it++)
	{
		if (isOp(*it))
			s.append("@");
		s.append((*it)->getNick());
		s.append(" ");
	}

	return (s);
}


// Setters

void	Channel::setName(std::string name) { this->_name = name; }

// Overloads

bool	Channel::operator==(Channel & obj)
{
	if (this->_name != obj._name)
		return (0);
	return (1);
}

// Other functions

void	Channel::deleteUser(User * user)
{
	std::string s;
	for (std::list<User *>::iterator it = this->_users.begin(); it != this->_users.end(); ++it)
    {
		if (*it == user) // Esto no se si esta bien
		{
			this->_users.erase(it);
			for (std::list<User *>::iterator it2 = this->_operators.begin(); it2 != this->_operators.end(); ++it2)
			{
				if (*it2 == user)
				{
					this->_operators.erase(it2);
					if (!this->_operators.size())
						this->_operators.push_back(*(this->_users.begin()));
					break ;
				}
			}
			s += user->getNick() + " has left the channel " + this->_name + "\r\n";
			sendMsgChannel(s);
			return ;
		}
	}
}

void	Channel::addUser(User * user)
{
	this->_users.push_back(user);
	if (_users.size() >= this->_maxusers)
		this->_isfull = true;
}

// krios-fu
void	Channel::sendMsgChannel( std::string msg , int fd)
{
	for (std::list<User*>::iterator it = this->_users.begin(); it != this->_users.end(); it++)
	{
		if ( (*it)->getsockfd() != fd )
			send((*it)->getsockfd(), msg.c_str(), msg.length(), 0);
	}
}

void	Channel::sendMsgChannel(std::string msg)
{
	for (std::list<User*>::iterator it = this->_users.begin(); it != this->_users.end(); it++)
	{
		send((*it)->getsockfd(), msg.c_str(), msg.length(), 0);
	}
}