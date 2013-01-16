#ifndef __GAME__
#define __GAME__

#include <list>
#include <map>
#include "./../../Abs_Socket/ISocket.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "RectangleCollisionDefinition.hpp"
#include "./../../../protocol.h"
#include "MovingObstacle.hpp"
#include "LifePowerUp.hpp"
#include <iostream>
#include <string.h>
#include <cstdlib>

class IAUnit;
class HumainUnit;
class Game
{
private:
  int _id;
  std::list<IAUnit*>		iaList;
  std::list<HumainUnit*>	humainList;
  std::list<Player*>		playerList;
  std::list<Bullet*>		bulletList;
  std::list<MovingObstacle*>	obsList;
  std::list<LifePowerUp*>	bonusList;
public:
  Game(int id);
  void* operator()(void*);
  // TODO operator for win
  void loop();
  void update(double time);
  void collision();
  IAUnit* createAIUnit(int id, std::pair<float, float> speed, ICollisionDefinition *coll, int health, int strength, bool isDestroyable, Protocol::type_drawable type, Protocol::patern_enemie patern);
  HumainUnit* createHumainUnit(int id, std::pair<float, float> speed, int health, int strength, bool isDestroyable, Player *p);
  MovingObstacle* createLinearMovingObstacle(int id, std::pair<float, float> speed, ICollisionDefinition *coll, int strength, bool isDestroyable);
  Player* createPlayer(int id, std::string name, ISocket *socket_tcp, ISocket *socket_udp);
  LifePowerUp* createBonus(int nb_life, int id, ICollisionDefinition *coll, bool isDestroyable, int strength);
  Bullet *createBullet(int idUnit, std::pair<float, float> speed, int id, ICollisionDefinition *rec, int strength, bool isDestroyable, Protocol::type_drawable);
 
  Bullet *getBullet(int id)const;
  HumainUnit *getUnitByPlayer(Player *p)const;
  HumainUnit *getUnitHuman(int id)const;
  HumainUnit* addHumainUnitByPlayer(Player *p);
  IAUnit *getUnitAI(int id)const;
  Unit *getUnit(int id)const;
  MovingObstacle *getObs(int id)const;
  LifePowerUp *getLifePowerUp(int id)const;
  Player *getPlayer(int id)const;
  void addPlayer(std::string, ISocket *, ISocket *);
  int getNbPlayer()const;
  Player *getPlayerBySockTcp(ISocket *socket_tcp)const;
  Player *getPlayerBySockUdp(ISocket *socket_udp)const;
  int getId()const;

  void eraseBullet(int id);
  void eraseBulletsPlayer(int idPlayer);
  void erasePlayer(int id);
  void eraseHumain(int id);
  void eraseIa(int id);
  void eraseObs(int id);
  void eraseBonus(int id);
  
  void eraseAllIa();
  void eraseAllObs();
  void eraseAllBonus();
  void resetLife();
  void resetGame(double *time);
  bool allDead();

  bool isFriendlyBullet(Bullet *b);
  bool collisionIaWithBullet(IAUnit *u);
  bool collisionHumainWithBullet(HumainUnit *u);
  bool collisionWithEnemie(HumainUnit *u);
  bool collisionUWithObs(Unit *u);
  bool collisionBWithObs(Bullet *b);
  bool collisionWithBonus(HumainUnit *u);

  void fire_ia(int id);
  void fire(int id);
  void move(int id, Protocol::move *m);

  void createRandomObs(double time);
  void createRandomBonus(double time);
  void createRandomEnemie(double time);
  void CreateEnemiePaternVFLY(Protocol::type_drawable type, int);
  void CreateEnemiePaternLine(Protocol::type_drawable type, int);
  void CreateEnemiePaternOneToThree(Protocol::type_drawable type, int);

  int getIaSize()const;
  int getHumainSize()const;
  int getBulletSize()const;
  int getObsSize()const;
  int getBonusSize()const;

  void sendGame()const;
  void sendBullet()const;
  void sendObs()const;
  void sendIA()const;
  void sendBonus()const;
  void sendShip()const;
};

#endif //__GAME__

#include "IAUnit.hpp"
#include "HumainUnit.hpp"
