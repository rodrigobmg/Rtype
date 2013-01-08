//
// UServerSocket.h for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Sat Jan  5 16:52:46 2013 marche_m (Maxime Marchès)
// Last update Mon Jan  7 16:20:01 2013 marche_m (Maxime Marchès)
//

#ifndef __U_SERVER_SOCKET__
# define __U_SERVER_SOCKET__

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <map>

#include "IServerSocket.h"
#include "USocket.h"

class UServerSocket : public IServerSocket
{
public:
  UServerSocket();
  virtual	~UServerSocket();
  bool		init(std::string const & listenHost, std::string const & listenPort);
  ISocket	* myaccept();
  void		launch();

private:
  void		addNewPeer(void * peer);
  int		getSocket() { return _listenSocket; }
  int		selectSockets();
  void		interpretCmd(std::list<int>::iterator & it);

  struct sockaddr_in		_servAddr;
  int				_listenSocket;
  std::list<int>		_clientsList;
  std::map<int, ISocket *>	_clientsSocksMap;
  fd_set			_readFd;
};


#endif