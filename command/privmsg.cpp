
#include "../server/Server.hpp"
#include "../utils.hpp"

void	Server::privmsg_command(std::string & command, int & fd)
{
	std::string 				delimiter = " ";
	size_t						pos = 0;
	std::string 				token;
	int							deliver_fd;
	std::list<User *>::iterator it;
	std::string					s;
	std::string					message;

	//std::string					aux(command);

	if ((pos = command.find(delimiter)) == std::string::npos)
	{
		s.assign(":No recipient given (PRIVMSG)");
		return (send_error(ERR_NORECIPIENT, s, fd));
	}
	command.erase(0, pos + delimiter.length());
	while (command.begin() != command.end() && *(command.begin()) == ' ')
		command.erase(0, 1);
	if (command.begin() == command.end())
	{
		s.assign(":No recipient given (PRIVMSG)");
		return (send_error(ERR_NORECIPIENT, s, fd));
	}
	if ((pos = command.find(delimiter)) == std::string::npos)
		return (send_error(ERR_NOTEXTTOSEND, ":No text to send", fd));
	token = command.substr(0, pos);
	while (command.begin() != command.end() && *(command.begin()) == ' ')
		command.erase(0, 1);
	std::cout << "el target es !" << token << "!\n";
	for (it = this->_connected_users.begin(); it != this->_connected_users.end(); ++it)
	{
		if ((*it)->getNick() == token)
		{
			deliver_fd = (*it)->getsockfd();
			break ;
		}
	}
	// Si hemos encontrado el nick, mandamos el mensaje
	if (it != this->_connected_users.end())
	{
		command.erase(0, pos + delimiter.length());
		while (command.begin() != command.end() && *(command.begin()) == ' ')
			command.erase(0, 1);
		if (command.begin() == command.end())
			return (send_error(ERR_NOTEXTTOSEND, ":No text to send", fd));
		if (!(*(command.begin()) == ':'))
		{
			s.assign(token);
			s.assign(" : Too many recipients.");
			return (send_error(ERR_TOOMANYTARGETS, s, fd));
		}
		else
			command.erase(0, 1);
		if (command.begin() == command.end())
			return (send_error(ERR_NOTEXTTOSEND, ":No text to send", fd));
		message.append("PRIVMSG " + token + " :" + command);
		return (send_message(message, deliver_fd, this->_fd_users[fd]));
	}
	// Ahora vamos al caso de mandar un mensaje a un todo un canal
	// Mandamos un error si no hemos encontrado el token ni en los nicks ni en los channels
	if (this->_name_channel.find(token) == this->_name_channel.end())
	{
		s.assign(token);
		s.assign(" :No such nick/channel");
		return (send_error(ERR_NOSUCHNICK, s, fd));

	}
	else
	{
		command.erase(0, pos + delimiter.length());
		while (command.begin() != command.end() && *(command.begin()) == ' ')
			command.erase(0, 1);
		if (command.begin() == command.end())
			return (send_error(ERR_NOTEXTTOSEND, ":No text to send", fd));
		if (!(*(command.begin()) == ':'))
		{
			s.assign(token);
			s.assign(" : Too many recipients.");
			return (send_error(ERR_TOOMANYTARGETS, s, fd));
		}
		else
			command.erase(0, 1);
		if (command.begin() == command.end())
			return (send_error(ERR_NOTEXTTOSEND, ":No text to send", fd));
		message.append("PRIVMSG " + token + " :" + command);
		return (send_message_channel(message, this->_fd_users[fd], this->_name_channel[token]));
	}
}
