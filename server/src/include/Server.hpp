#ifndef __SERVER__
#define __SERVER__

#include "Player.hpp"
#include "Game.hpp"

#include "../../Abs_Socket/portaSocket.hpp"
//#include "../../Abs_Thread_mutex/portaThread.hpp"

class Server
{
public:
  std::list<Player *>	playerListWaiting;
  std::list<Game *>	gameList;
  std::list<MyThread*>	threadList;
  MyServerSocket*	server_socket;
public:
  Server(std::string const & port);
  
  int getNbGame()const;

  Player *getPlayerWaitingByTcp(ISocket * sock)const;
  Player *getPlayerWaiting(int id)const;
  Game *getGame(int id)const;
  std::list<Game*> &getGameList();

  void erasePlayerWaiting(int id);
  void eraseGame(int id);
  
  Player* createPlayerWaiting(int id, std::string name, ISocket *socket_tcp, ISocket *socket_upd);
  void createGame(int id);
  void launchGame(int id);
};

#endif
