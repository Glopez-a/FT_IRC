/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 20:39:45 by isfernan          #+#    #+#             */
/*   Updated: 2021/11/18 18:40:56 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"

// Constructor && destructor

User::User(int & fd, struct sockaddr_in const & addr) : _sock_fd(fd)
{
	init_modes();
	this->_addr = addr;
	this->_is_registered = false;
	this->_max_channels = false;
	this->_ping_status = false;
	this->_is_send_msg = false;
	this->_time_ping = 30000;
	this->_buffer_cmd = "";
}

User::~User() { }

// Getters

std::string User::getUserName() const { return (this->_username); }

std::string const & User::getNick() const { return (this->_nick); }

bool	User::getmode(char mode) const
{
	switch (mode)
	{
		case 'a':
			return (this->_modes.a);
		case 'i':
            return (this->_modes.i);
		case 'w':
            return (this->_modes.w);
		case 'r':
            return (this->_modes.r);
		case 'o':
            return (this->_modes.small_o);
		case 'O':
            return (this->_modes.big_o);
		case 's':
            return (this->_modes.s);
		default:
			return ( false );
	}
}


int		User::getsockfd()  const { return (this->_sock_fd); }


std::string const & User::getRealName() const { return this->_realName; }

bool	User::getRegistered() const { return (this->_is_registered); }

bool	User::getMaxChannels() const { return (this->_max_channels); }

bool const & User::getPingStatus() const { return this->_ping_status ; }

std::list< Channel *> & User::getChannels() { return this->_channels; }

std::string				User::getChannelsString()
{
	std::string s;

	for (std::list<Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++)
		s += (*it)->getName() + ",";
	return (s);
}

std::string const & User::getPing() const { return this->_ping; }
uint64_t const & User::getLastTime() const { return this->_lastTime; }
uint64_t const & User::getTimePing() const { return this->_time_ping; }
std::string const & User::getBufferCmd() const { return this->_buffer_cmd; }
bool const & User::getIsSendMsg() const { return this->_is_send_msg; }

std::string User::getAnswer()
{
	std::string tmp;

	if ( this->_answer.size() > 0)
	{
		tmp = this->_answer[0];
		this->_answer.pop_front();
	}
	
	return tmp;
}

bool	User::getPassState() const { return (this->_passState); }

std::string const & User::getMask() const { return this->_mask; }





// Setters

void	User::setUserName(std::string name) { this->_username = name; }

void 	User::setPing( std::string const & ping ) { this->_ping = ping; }
void	User::setPingStatus( bool const &  status ) { this->_ping_status = status; }

void	User::setLastTime ( uint64_t const & time ) { this->_lastTime = time; }

void	User::setTimePing ( uint64_t const & time ) { this->_time_ping = time; }


void	User::setNick(std::string nick) { this->_nick = nick; }

void	User::setmode(char mode, bool state)
{
	switch (mode)
	{
		case 'a':
			(this->_modes.a = state);
			break ;
		case 'i':
            (this->_modes.i = state);
			break ;
		case 'w':
            (this->_modes.w = state);
			break ;
		case 'r':
            (this->_modes.r = state);
			break ;
		case 'o':
            (this->_modes.small_o = state);
			break ;
		case 'O':
            (this->_modes.big_o = state);
			break ;
		case 's':
            (this->_modes.s = state);
			break ;
		default:
			break ;
	} 
}

void	User::setRegistered(bool status) { this->_is_registered = status; }

void	User::setRealName(std::string const &  realName) { this->_realName = realName; }

void	User::setAnswer(std::string const & answer)
{

	this->_answer.push_back( answer );
}

void	User::setBufferCmd( std::string const & buffer_cmd )
{
	this->_buffer_cmd = buffer_cmd;
}

void	User::setIsSendMsg( bool const & status ) { this->_is_send_msg = status ; }

void	User::setPassState(bool status) { this->_passState = status; }

void	User::setMask( void )
{
	std::string mask;
	if ( !this->_mask.length() )
	{
		mask = ":" + this->getNick() + "!" + this->getUserName() + "@" + this->getIp();
		this->_mask = mask;
	}
}


// Overloads

bool	User::operator==(User & obj)
{
	if (this->_nick != obj._nick)
		return (0);
	return (1);
}

// Other functions

std::string	User::showModes()
{
	std::string s = "";
	if (this->_modes.small_o == true)
		s += "o";
	if (this->_modes.i == true)
		s += "i";
	return s;
}

void	User::init_modes()
{
	this->_modes.a = false;
	this->_modes.i = false;
	this->_modes.w = false;
	this->_modes.r = false;
	this->_modes.small_o = false;
	this->_modes.big_o = false;
	this->_modes.s = false;
}

void	User::deleteChannel(Channel * channel)
{
	for (std::list<Channel *>::iterator it = this->_channels.begin(); it != this->_channels.end(); ++it)
    {
		if (*it == channel)
		{
			this->_max_channels = false;
			it = this->_channels.erase(it);
			return ;
		}
	}
}



void	User::addChannel(Channel *  channel)
{
	this->_channels.push_back(channel);
	if (_channels.size() >= MAX_CHANNELS)
		this->_max_channels = true;
}



std::string User::getIp(  ) const 
{
	struct in_addr clientIP;
	clientIP = this->_addr.sin_addr;
	char ipStr[INET_ADDRSTRLEN];
	return inet_ntop(AF_INET, &clientIP, ipStr, INET_ADDRSTRLEN);
}