//
// InterpretPackage.cpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server/src
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Wed Jan  9 10:54:24 2013 marche_m (Maxime Marchès)
// Last update Sun Jan 20 10:42:42 2013 mathieu leurquin
//

#include "../include/InterpretPackage.hpp"

InterpretPackage::InterpretPackage(Server *s)
{
  _funcMap[Protocol::REGISTER] = &InterpretPackage::execRegister;
  _funcMap[Protocol::LOGIN] = &InterpretPackage::execLogin;
  _funcMap[Protocol::GET_GAME_LIST] = &InterpretPackage::execGetGameList;
  _funcMap[Protocol::JOIN_GAME] = &InterpretPackage::execJoinGame;

  _funcMap[Protocol::CREATE_GAME] = &InterpretPackage::execCreateGame;
  //_funcMap[Protocol::MOVE] = &InterpretPackage::execMove;
  //_funcMap[Protocol::FIRE] = &InterpretPackage::execFire;
  _server = s;
}

void	InterpretPackage::executeCmd(void * header, void * data, ISocket * sock)
{
  if (header == 0 && data == 0) // Client disconnected on TCP socket
    {
      execExit(sock);
      return ;
    }
  if (sock->isUDP() == true)
    {
      // std::cout<<"receive something Udp"<<std::endl;
      Protocol::cmd_client * cmd = ((Protocol::cmd_client*)data);
      if (cmd->fire == true)
	this->execFire(data, sock);
      else
	{
	  // std::cout<<"move"<<std::endl;
	  Protocol::move * m = new Protocol::move;
	  memset(m, 0, sizeof(*m));
	  if (cmd->top == true)
	    m->top = 1;
	  if (cmd->down == true)
	    m->down = 1;
	  if (cmd->left == true)
	    m->left = 1;
	  if (cmd->right == true)
	    m->right = 1;
	  this->execMove(m, sock);
	}
      return ;
    }
  std::cout << "executeCmdTcp" << std::endl;
  int hdTmp[2];
  
  memcpy(hdTmp, header, 2 * sizeof(int));
  void (InterpretPackage::*pMethod)(void *, ISocket *) = (this->_funcMap[((Protocol::type_cmd)hdTmp[0])]);
  (this->*pMethod)(data, sock);
}

void	InterpretPackage::execExit(ISocket * sock)
{
  Player *p;
  
  for (std::list<Game*>::iterator it = _server->gameList.begin(); it != _server->gameList.end(); it++)
    if ((p = (*it)->getPlayerBySockTcp(sock)) != NULL)
      {
	(*it)->eraseHumain(p->getId());
	(*it)->erasePlayer(p->getId());
      }
  
}

void	InterpretPackage::execRegister(void * data, ISocket * sock)
{
  (void)data;
  (void)sock;
}

void	InterpretPackage::execLogin(void * data, ISocket * sock)
{
  (void)sock;
  std::cout << "execLogin" << std::endl;
  Protocol::login * dataTmp = new Protocol::login();
  memset(dataTmp, 0, sizeof(*dataTmp));
  memcpy(dataTmp, data, sizeof(*dataTmp));
  std::cout << dataTmp->login << std::endl;
  std::cout << dataTmp->passwd << std::endl;
}

void	InterpretPackage::execGetGameList(void * data, ISocket * sock)
{
  void	*res;
  int	size = 0;
  int position = 0;

  (void)data;

  size = sizeof(Protocol::parties) + (_server->getNbGame() * sizeof (Protocol::party));
  res = new char[size];

  Protocol::parties *pa = new Protocol::parties();
  pa->nb_parties = _server->getNbGame();
  memcpy((((char*)res) + position), pa, sizeof(*pa));
  position = sizeof(*pa);

  std::list <Game*> listGameCpy = _server->gameList;
  for (std::list<Game*>::iterator it = listGameCpy.begin(); it != listGameCpy.end(); it++)
    {
      Protocol::party *pa = new Protocol::party();
      pa->nb_players = (*it)->getNbPlayer();
      memcpy((((char*)res) + position), pa, sizeof(*pa));
      position += sizeof(*pa);
    }
  sock->sendv(size, res);
}

void	InterpretPackage::execJoinGame(void * data, ISocket * sock)
{
  std::list <Game*> listGameCpy = _server->gameList;
  Protocol::join_game *game = new Protocol::join_game();

  memset(game, 0, sizeof(*game));
  memcpy(game, data, sizeof(Protocol::join_game));
  for (std::list<Game*>::iterator it = listGameCpy.begin(); it != listGameCpy.end(); it++)
    {
      Protocol::response *rep = new Protocol::response();
      if ((*it)->getId() == game->id && (*it)->getNbPlayer() < 4)
	{
	  Player *p = _server->getPlayerWaitingByTcp(sock);
	  
	  (*it)->addPlayer(p);
	  _server->erasePlayerWaiting(p->getId());
	  rep->response = Protocol::VALIDE;
	  sock->sendv(sizeof(Protocol::response), (void*)rep);
	  return;
	}
      else if ((*it)->getId() == game->id && (*it)->getNbPlayer() >= 4)
 	{
	  rep->response = Protocol::CANT_JOIN_GAME;
	  sock->sendv(sizeof(Protocol::response), (void*)rep);
	  return;
	}
    }
}

void	InterpretPackage::execCreateGame(void * data, ISocket * sock)
{
  _server->createGame(1);
  Player *p = _server->getPlayerWaitingByTcp(sock);


#ifdef __unix__
      usleep(50000);
#endif
#ifdef _WIN32
      Sleep(50);
#endif
  if (p == NULL)
      return ;
  if (_server->gameList.back() == NULL)
    return;
  _server->gameList.back()->addPlayer(p);
  _server->erasePlayerWaiting(p->getId());
  Protocol::response *rep = new Protocol::response();
  rep->response = Protocol::VALIDE;
  sock->sendv(sizeof(*rep), rep);
}

void	InterpretPackage::execMove(Protocol::move * data, ISocket * sock)
{
  Player *p;
  
  for (std::list<Game*>::iterator it = _server->gameList.begin(); it != _server->gameList.end(); it++)
    {
      if ((p = (*it)->getPlayerBySockUdp(sock)) != NULL)
	{
	  // std::cout << "je move un player list size : "<<(*it)->playerList.size() << std::endl;
	  (*it)->move(p->getId(), data);
	  // Protocol::response *rep = new Protocol::response();
	  // rep->response = Protocol::VALIDE;
	  // sock->sendv(sizeof(Protocol::response*), (void*)rep)
	  ;
	}
    }
}

void	InterpretPackage::execFire(void * data, ISocket * sock)
{
  (void)data;
  Player *p;
  std::list <Game*> listGameCpy = _server->gameList;
  
  for (std::list<Game*>::iterator it = listGameCpy.begin(); it != listGameCpy.end(); it++)
    {
      if ((p = (*it)->getPlayerBySockUdp(sock)) != NULL)
	{
	  (*it)->fire(p->getId());
 	  // Protocol::response *rep = new Protocol::response();
	  // rep->response = Protocol::VALIDE;
	  // sock->sendv(sizeof(*rep), (void*)rep);
	}
    }
}
