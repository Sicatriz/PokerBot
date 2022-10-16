#ifndef MIGUEL_H
#define MIGUEL_H

#include "player.h"
#include "game.h"
#include "playerid.h"


namespace PXL2022
{

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

class MiStatistics
{
public:

    int lastPlayNummer[4] = {0,0,0,0};
        int wins[4] = {0,0,0,0};
        int loss[4] = {0,0,0,0};
        int prevChips[4] = {128,128,128,128};

    // algoritme om bij te houden bij welke bedragen / Qblinds een bepaalde speler fold (bijhouden per spelerID)
   //     int playStats[][];


};

class Miguel : public Player
{
public:
    Miguel( unsigned char instance = 0) : Player(instance) {}
    const char* getName( void ) const; // {return "Bitch Killer";}
    int willYouRaise( unsigned int totalBet );

private:

   int miPosition;

   int miOnTable()
   {
        for(int i = 0 ; i < 4;i++)
        {

        }
   }

   float raiseRatio()
   {
       int ratio = getGame()->getHighestBet() / getGame()->getBlind();
       return ratio;
   }

   static MiStatistics stats[MAX_PLAYER_ID];

};



}
#endif // MIGUEL_H
