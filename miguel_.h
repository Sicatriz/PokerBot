#ifndef MIGUEL_H
#define MIGUEL_H

#include "player.h"
#include "game.h"

namespace PXL2022
{

class Miguel : public Player //Miguel "is" a Player
{
public: //Everything below this line is publicly accessible
    Miguel( unsigned char instance = 0 ) : Player(instance) {} //Constructor with parameter "instance" (i.e. 0->3) and forward to Player constructor
    const char* getName( void ) const {return "BitchesKiller";} //Overwrite this pure virtual function to define the name for printing
    int willYouRaise( unsigned int totalBet ); //Overwrite the pure virtual function to define the way of playing
private:
	bool checked = true;
	void talkSmack();

};

class MiHand
{
    public:
        float raiseRatio;
        float miBetCheck()
        {
            raiseRatio = Game().getBlind() / (Game().getBlind() + Game().getHighestBet() );
            return raiseRatio;
        }
};

class MiPosition
{
    public:
        int meToButton;
        float miAggro;

        float miAggroC()
        {
          meToButton = 0;  // 0 = formule position to button moet nog geschreven

          switch (meToButton) {
          case 0:
              miAggro = 2;
              break;
          case 1:
              miAggro = 1.6;
              break;
          case 2:
              miAggro = 1.2;
              break;
          case 3:
              miAggro = 0.8;
              break;
          default:
              miAggro = 0.2;
              break;
          }
          return miAggro;
        }


};


}
#endif // MIGUEL_H
