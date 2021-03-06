/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:18:55 by isfernan          #+#    #+#             */
/*   Updated: 2021/11/18 18:04:34 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../server/Server.hpp"
#include "../utils.hpp"

void    Server::privmsg_command( std::vector<std::string> const & parse, User *usr )
{

    list_user_it    start_usr = this->_connected_users.begin();
    list_user_it    end_usr = this->_connected_users.end();
    User            *usr_dest;
    Channel         *chnl_dest;
    std::string     message;
    bool            dest_user_b, dest_chnl_b;

    dest_user_b = false;
    dest_chnl_b = false;
    

    if ( parse.size() < 2 )
        return send_error(ERR_NORECIPIENT, ":No recipient given (PRIVMSG)", usr);
    std::string     dest = parse[1];
    for (; start_usr != end_usr ; ++start_usr )
    {
        if ( ft_toupper( (*start_usr)->getNick() ) == ft_toupper(dest) )
        {
            usr_dest = *start_usr;
            dest_user_b = true;
            if (parse.size() == 2)
                send_error(ERR_NOTEXTTOSEND, ":No text to send", usr);
            break ;
        }
    }

    if( this->_name_channel.count(dest) > 0 )
    {
        dest_chnl_b = true;
        chnl_dest =  this->_name_channel.at(dest);

        if (chnl_dest->isBanned(usr->getMask()))
            return send_error(ERR_CANNOTSENDTOCHAN, " " + chnl_dest->getName() + " :You are banned", usr);
    }
    if ( !dest_user_b && !dest_chnl_b )
        return send_error( ERR_NOSUCHNICK,  parse[1] + " :no such nick/channel", usr );
    {
        std::string tmp;
        for (size_t i = 2; i < parse.size(); i++ )
        {
            tmp.append( parse[i] );
            if ( i < ( parse.size() - 1) )
                tmp.append(" ");
        }
            message.append("PRIVMSG " + dest + " :" + tmp);
    }

    if (dest_user_b)
        return send_message( message, usr_dest, usr );
    if (dest_chnl_b)
        return send_message_channel_block( message, usr, chnl_dest );
}