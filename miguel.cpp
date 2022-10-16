#include "miguel.h"
#include "game.h"

namespace PXL2022
{
MiStatistics Miguel::stats[MAX_PLAYER_ID];

const char * Miguel::getName( void ) const
{
    if( instance == 0 )
    {
        return "Miguel MK1";
    }
    if( instance == 1 )
    {
        return "Miguel P. Ivey";
    }
    if( instance == 2 )
    {
        return "Miguel Negreanu";
    }
    return "Miguel Snottebel";
}

int Miguel::willYouRaise( unsigned int totalBet)
{

    for(int i = 0 ; i < getGame()->getPlayers().size();i++)
    {
        Player* player = getGame()->getPlayers().at(i);
        if(stats[player->getID()].lastPlayNummer[player->getInstance()] != getGame()->getPlays())
        {
            if(player->getChips() > stats[player->getID()].prevChips[player->getInstance()])
            {
                stats[player->getID()].wins[player->getInstance()]++;// = stats[player->getID()].wins[player->getInstance()] +1;
            }
            else if(player->getChips() < stats[player->getID()].prevChips[player->getInstance()])
            {
                stats[player->getID()].loss[player->getInstance()]++;// = stats[player->getID()].loss +1;
            }
            stats[player->getID()].lastPlayNummer[player->getInstance()] = getGame()->getPlays();
            stats[player->getID()].prevChips[player->getInstance()] = player->getChips();
        }
    }

    PokerRank mijnHandRank = getRank();
    miPosition = getGame()->getPlayers().size() - getGame()->getDealerLocation();
        //PRE FLOP
        if( getTable()->isPreFlop() )
        {            
            // FOR ALL INSTANCES!!
            //POCKETS >10
            if( getHand().getFirstCard()->getRank() == getHand().getSecondCard()->getRank() && getHand().getFirstCard()->getRank() > 10 )
            {
                if(miPosition < 3 ) // mijn positie == laatste 3 posities
                {
                    if(raiseRatio() <= getGame()->getBlind()) // geen bet groter dan de blinds ==> blinds *3
                    {
                        return getGame()->getBlind() * 3;
                    }
                    else if(raiseRatio() <= getGame()->getBlind() * 6) // highbet <= 6 blinds ==> call
                    {
                        return 0;
                    }
                    else if(getHand().getFirstCard()->getRank() > 12)  // KK of AA bij groter highbet ==> all in
                    {
                        return getChips();
                    }
                    else
                        return -1;
                }
                else  // vroegere posities
                    if(getHand().getFirstCard()->getRank() > 12)  // KK of AA bij groter highbet ==> blinds *6
                    {
                        return getGame()->getBlind() * 6;
                    }
                    else if(raiseRatio() <= getGame()->getBlind()) // geen bet groter dan de blinds ==> blinds *3
                    {
                        return getGame()->getBlind() * 3;
                    }
                    else if(raiseRatio() <= getGame()->getBlind() * 6) // highbet <= 6 blinds ==> call
                    {
                        if(getHand().getFirstCard()->getRank() > 12){return getChips();}

                        return 0;
                    }
                    else
                        return -1;
            }

            // 2 KAARTEN >= 10
            if( getHand().getFirstCard()->getRank() >= 10 && getHand().getSecondCard()->getRank() >= 10 )
            {
                if(miPosition < 3 ) // mijn positie == laatste 3 posities
                {
                    if(raiseRatio() <= getGame()->getBlind()) // geen bet groter dan de blinds ==> blinds *3
                    {
                        return getGame()->getBlind() * 3;
                    }
                    else if(raiseRatio() <= getGame()->getBlind() * 6) // highbet <= 6 blinds ==> call
                    {
                        return 0;
                    }
                    else if(getHand().getFirstCard()->getRank() > 12)  // KK of AA bij groter highbet ==> all in
                    {
                        return getChips();
                    }
                    else
                        return -1;
                }
                else
                    if(raiseRatio() <= getGame()->getBlind()) // geen bet groter dan de blinds ==> blinds *3
                    {
                        return 0;
                    }
                    else if(raiseRatio() <= getGame()->getBlind() * 6) // highbet <= 6 blinds ==> call
                    {
                        if(getGame()->getHighestBet() < getChips() / 15)
                        {
                        return 0;
                        }
                        return -1;
                    }
                    else if(getHand().getFirstCard()->getRank() > 12)  // KK of AA bij groter highbet ==> all in
                    {
                        return getChips();
                    }
                    else
                        return -1;

            }

            switch (instance) {
            case 0:
                if(getGame()->getPlays() < 60)
                {
                    //POCKETS <=10
                    if( getHand().getFirstCard()->getRank() == getHand().getSecondCard()->getRank() && getHand().getFirstCard()->getRank() < 11 )
                    {
                        if(miPosition < 2 ) // mijn positie == laatste 2 posities
                        {
                            if(raiseRatio() <= getGame()->getBlind()) // geen bet groter dan de blinds ==> blinds *3
                            {
                                return getGame()->getBlind() * 3;
                            }
                            else if(raiseRatio() <= getGame()->getBlind() * 6) // highbet <= 6 blinds ==> call
                            {
                                if(getHand().getFirstCard()->getRank() >7){ return 0;} // indien >77 ==> call
                            }
                            else
                                return -1;
                        }
                        else  // vroegere posities
                            if(raiseRatio() <= getGame()->getBlind()) // geen bet groter dan de blinds ==> call
                            {
                                return 0;
                            }
                            else if(raiseRatio() <= getGame()->getBlind() * 3) // highbet <= 6 blinds ==> call
                            {
                                if(getGame()->getPlayers().size() < 5){return 0;}
                            }
                            else
                                return -1;
                    }
                }
                else // vanaf ronde 60
                    //POCKETS <=10
                    if( getHand().getFirstCard()->getRank() == getHand().getSecondCard()->getRank() && getHand().getFirstCard()->getRank() < 11 )
                    {
                        if(miPosition < 2 ) // mijn positie == laatste 2 posities
                        {
                            if(raiseRatio() <= getGame()->getBlind()) // geen bet groter dan de blinds ==> blinds *3
                            {
                                return getGame()->getBlind() * 3;
                            }
                            else if(raiseRatio() <= getGame()->getBlind() * 6) // highbet <= 6 blinds ==> call
                            {
                                if(getGame()->getPlayers().size() < 5){ return 0;} // indien <5 spelers in het spel ==> call
                            }
                            else
                                if(getChips() > totalBet * 4){ return getChips();}
                                return -1;
                        }
                        else  // vroegere posities
                            if(raiseRatio() <= getGame()->getBlind()) // geen bet groter dan de blinds ==> call
                            {
                                return 0;
                            }
                            else if(raiseRatio() <= getGame()->getBlind() * 3) // highbet <= 6 blinds ==> call
                            {
                                if(getGame()->getPlayers().size() < 5){return 0;}
                            }
                            else
                                return -1;
                    }

                //SUITED hands
                if( getHand().getFirstCard()->getSuit() == getHand().getSecondCard()->getSuit() )
                {
                    int diffBetweenOrderedCards = mijnHandRank.getHand().at(0) - mijnHandRank.getHand().at(1);
                    if( diffBetweenOrderedCards == 1 || diffBetweenOrderedCards == 13 )
                    { //suited connected
                        // eerste 60 rondes
                        if(getGame()->getPlays() < 60)
                        {
                            //beide connectSuits zijn >10
                            if(getHand().getFirstCard()->getRank() > 10 && getHand().getSecondCard()->getRank() > 10)
                            {
                                if (MiHand().miBetCheck() > 0.5)
                                {
                                        return ( getGame()->getBlind() * 5);
                                }
                                else if( getGame()->getHighestBet() < getChips() / 12  )
                                {
                                        return getGame()->getHighestBet() * 3;
                                }
                                else if( getGame()->getHighestBet() > getChips() / 12 && (getGame()->getHighestBet() < getChips() / 5 ) )
                                {
                                        return 0;
                                }
                                else
                                        return -1;
                            }

                            //suited connects < 10
                            if (MiHand().miBetCheck() > 0.5)
                            {
                                return ( getGame()->getBlind() * 3);
                            }
                            else if( getGame()->getHighestBet() > getChips() / 20 && (getGame()->getHighestBet() < getChips() / 10 ) )
                            {
                                return 0;
                            }
                            else
                                return -1;
                         }

                         // Vanaf ronde 60
                         if(getGame()->getPlays() >= 60)
                         {
                            //beide connectSuits zijn >10
                            if(getHand().getFirstCard()->getRank() > 10 && getHand().getSecondCard()->getRank() > 10)
                            {
                                if (MiHand().miBetCheck() > 0.5)
                                {
                                    return ( getGame()->getBlind() * 10);
                                }
                                else if( getGame()->getHighestBet() < getChips() / 12  )
                                {
                                    return getGame()->getHighestBet() * 3;
                                }
                                else if( getGame()->getHighestBet() > getChips() / 12 && (getGame()->getHighestBet() < getChips() / 5 ) )
                                {
                                    return 0;
                                }
                                else
                                    return -1;
                            }

                            //suited connects < 10
                            if (MiHand().miBetCheck() > 0.5)
                            {
                                return ( getGame()->getBlind() * 3);
                            }
                            else if( getGame()->getHighestBet() > getChips() / 25 && (getGame()->getHighestBet() < getChips() / 15 ) )
                            {
                                return 0;
                            }
                            else
                                return -1;
                         }

                         //suited Not connected maar dicht bij elkaar
                         if( diffBetweenOrderedCards > 1 && diffBetweenOrderedCards < 5 )
                         {
                            if (MiHand().miBetCheck() > 0.5)
                            {
                                return ( getGame()->getBlind() * 3);
                            }
                            else if( getGame()->getHighestBet() > getChips() / 30 && (getGame()->getHighestBet() < getChips() / 15 ) )
                            {
                                return 0;
                            }
                            else
                                 return -1;
                         }

                         // willekeurig suited
                         if (MiHand().miBetCheck() > 0.4)
                         {
                            return 0;
                         }
                         else
                            return -1;
                      }
                }
                break;
            case 1:
                if(getGame()->getPlays() < 40)
                {
                    //POCKETS <=10
                    if( getHand().getFirstCard()->getRank() == getHand().getSecondCard()->getRank() && getHand().getFirstCard()->getRank() < 11 )
                    {
                        if(miPosition < 2 ) // mijn positie == laatste 2 posities
                        {
                            if(raiseRatio() <= getGame()->getBlind()) // geen bet groter dan de blinds ==> blinds *3
                            {
                                return getGame()->getBlind() * 3;
                            }
                            else if(raiseRatio() <= getGame()->getBlind() * 6) // highbet <= 6 blinds ==> call
                            {
                                if(getHand().getFirstCard()->getRank() >7){ return 0;} // indien >77 ==> call
                            }
                            else
                                return -1;
                        }
                        else  // vroegere posities
                            if(raiseRatio() <= getGame()->getBlind()) // geen bet groter dan de blinds ==> call
                            {
                                return 0;
                            }
                            else if(raiseRatio() <= getGame()->getBlind() * 3) // highbet <= 6 blinds ==> call
                            {
                                if(getGame()->getPlayers().size() < 5){return 0;}
                            }
                            else
                                return -1;
                    }
                    else // vanaf ronde 40
                        //POCKETS <=10
                        if( getHand().getFirstCard()->getRank() == getHand().getSecondCard()->getRank() && getHand().getFirstCard()->getRank() < 11 )
                        {
                            if(miPosition < 2 ) // mijn positie == laatste 2 posities
                            {
                                if(raiseRatio() <= getGame()->getBlind()) // geen bet groter dan de blinds ==> blinds *3
                                {
                                    return getGame()->getBlind() * 3;
                                }
                                else if(raiseRatio() <= getGame()->getBlind() * 6) // highbet <= 6 blinds ==> call
                                {
                                    if(getGame()->getPlayers().size() < 5){ return 0;} // indien <5 spelers in het spel ==> call
                                }
                                else
                                    if(getChips() > totalBet * 4){ return getChips();}
                                    return -1;
                            }
                            else  // vroegere posities
                                if(raiseRatio() <= getGame()->getBlind()) // geen bet groter dan de blinds ==> call
                                {
                                    return 0;
                                }
                                else if(raiseRatio() <= getGame()->getBlind() * 3) // highbet <= 6 blinds ==> call
                                {
                                    if(getGame()->getPlayers().size() < 5){return 0;}
                                }
                                else
                                    return -1;
                        }
                    //SUITED hands
                    if( getHand().getFirstCard()->getSuit() == getHand().getSecondCard()->getSuit() )
                    {
                        int diffBetweenOrderedCards = mijnHandRank.getHand().at(0) - mijnHandRank.getHand().at(1);
                        if( diffBetweenOrderedCards == 1 || diffBetweenOrderedCards == 13 )
                        { //suited connected
                            // eerste 40 rondes
                            if(getGame()->getPlays() < 40)
                            {
                                //beide connectSuits zijn >10
                                if(getHand().getFirstCard()->getRank() > 10 && getHand().getSecondCard()->getRank() > 10)
                                {
                                    if (MiHand().miBetCheck() > 0.5)
                                    {
                                            return ( getGame()->getBlind() * 5);
                                    }
                                    else if( getGame()->getHighestBet() < getChips() / 12  )
                                    {
                                            return getGame()->getHighestBet() * 3;
                                    }
                                    else if( getGame()->getHighestBet() > getChips() / 12 && (getGame()->getHighestBet() < getChips() / 5 ) )
                                    {
                                            return 0;
                                    }
                                    else
                                            return -1;
                                }

                                //suited connects < 10
                                if (MiHand().miBetCheck() > 0.5)
                                {
                                    return ( getGame()->getBlind() * 3);
                                }
                                else if( getGame()->getHighestBet() > getChips() / 20 && (getGame()->getHighestBet() < getChips() / 10 ) )
                                {
                                    return 0;
                                }
                                else
                                    return -1;
                             }

                             // Vanaf ronde 40
                             if(getGame()->getPlays() >= 40)
                             {
                                //beide connectSuits zijn >10
                                if(getHand().getFirstCard()->getRank() > 10 && getHand().getSecondCard()->getRank() > 10)
                                {
                                    if (MiHand().miBetCheck() > 0.5)
                                    {
                                        return ( getGame()->getBlind() * 10);
                                    }
                                    else if( getGame()->getHighestBet() < getChips() / 12  )
                                    {
                                        return getGame()->getHighestBet() * 3;
                                    }
                                    else if( getGame()->getHighestBet() > getChips() / 12 && (getGame()->getHighestBet() < getChips() / 5 ) )
                                    {
                                        return 0;
                                    }
                                    else
                                        return -1;
                                }

                                //suited connects < 10
                                if (MiHand().miBetCheck() > 0.5)
                                {
                                    return ( getGame()->getBlind() * 3);
                                }
                                else if( getGame()->getHighestBet() > getChips() / 25 && (getGame()->getHighestBet() < getChips() / 15 ) )
                                {
                                    return 0;
                                }
                                else
                                    return -1;
                             }

                             //suited Not connected maar dicht bij elkaar
                             if( diffBetweenOrderedCards > 1 && diffBetweenOrderedCards < 5 )
                             {
                                if (MiHand().miBetCheck() > 0.5)
                                {
                                    return ( getGame()->getBlind() * 3);
                                }
                                else if( getGame()->getHighestBet() > getChips() / 30 && (getGame()->getHighestBet() < getChips() / 15 ) )
                                {
                                    return 0;
                                }
                                else
                                     return -1;
                             }

                             // willekeurig suited
                             if (MiHand().miBetCheck() > 0.4)
                             {
                                return 0;
                             }
                             else
                                return -1;
                          }
                    }
                }

                break;
            case 2:
                if(getGame()->getPlays() < 20)
                {
                    //POCKETS <=10
                    if( getHand().getFirstCard()->getRank() == getHand().getSecondCard()->getRank() && getHand().getFirstCard()->getRank() < 11 )
                    {
                        if(miPosition < 2 ) // mijn positie == laatste 2 posities
                        {
                            if(raiseRatio() <= getGame()->getBlind()) // geen bet groter dan de blinds ==> blinds *3
                            {
                                return getGame()->getBlind() * 3;
                            }
                            else if(raiseRatio() <= getGame()->getBlind() * 6) // highbet <= 6 blinds ==> call
                            {
                                if(getHand().getFirstCard()->getRank() >7){ return 0;} // indien >77 ==> call
                            }
                            else
                                return -1;
                        }
                        else  // vroegere posities
                            if(raiseRatio() <= getGame()->getBlind()) // geen bet groter dan de blinds ==> call
                            {
                                return 0;
                            }
                            else if(raiseRatio() <= getGame()->getBlind() * 3) // highbet <= 6 blinds ==> call
                            {
                                if(getGame()->getPlayers().size() < 5){return 0;}
                            }
                            else
                                return -1;
                    }
                    else // vanaf ronde 20
                        //POCKETS <=10
                        if( getHand().getFirstCard()->getRank() == getHand().getSecondCard()->getRank() && getHand().getFirstCard()->getRank() < 11 )
                        {
                            if(miPosition < 2 ) // mijn positie == laatste 2 posities
                            {
                                if(raiseRatio() <= getGame()->getBlind()) // geen bet groter dan de blinds ==> blinds *3
                                {
                                    return getGame()->getBlind() * 3;
                                }
                                else if(raiseRatio() <= getGame()->getBlind() * 6) // highbet <= 6 blinds ==> call
                                {
                                    if(getGame()->getPlayers().size() < 5){ return 0;} // indien <5 spelers in het spel ==> call
                                }
                                else
                                    if(getChips() > totalBet * 4){ return getChips();}
                                    return -1;
                            }
                            else  // vroegere posities
                                if(raiseRatio() <= getGame()->getBlind()) // geen bet groter dan de blinds ==> call
                                {
                                    return 0;
                                }
                                else if(raiseRatio() <= getGame()->getBlind() * 3) // highbet <= 6 blinds ==> call
                                {
                                    if(getGame()->getPlayers().size() < 5){return 0;}
                                }
                                else
                                    return -1;
                        }
                    //SUITED hands
                    if( getHand().getFirstCard()->getSuit() == getHand().getSecondCard()->getSuit() )
                    {
                        int diffBetweenOrderedCards = mijnHandRank.getHand().at(0) - mijnHandRank.getHand().at(1);
                        if( diffBetweenOrderedCards == 1 || diffBetweenOrderedCards == 13 )
                        { //suited connected
                            // eerste 20 rondes
                            if(getGame()->getPlays() < 20)
                            {
                                //beide connectSuits zijn >10
                                if(getHand().getFirstCard()->getRank() > 10 && getHand().getSecondCard()->getRank() > 10)
                                {
                                    if (MiHand().miBetCheck() > 0.5)
                                    {
                                            return ( getGame()->getBlind() * 5);
                                    }
                                    else if( getGame()->getHighestBet() < getChips() / 12  )
                                    {
                                            return getGame()->getHighestBet() * 3;
                                    }
                                    else if( getGame()->getHighestBet() > getChips() / 12 && (getGame()->getHighestBet() < getChips() / 5 ) )
                                    {
                                            return 0;
                                    }
                                    else
                                            return -1;
                                }

                                //suited connects < 10
                                if (MiHand().miBetCheck() > 0.5)
                                {
                                    return ( getGame()->getBlind() * 3);
                                }
                                else if( getGame()->getHighestBet() > getChips() / 20 && (getGame()->getHighestBet() < getChips() / 10 ) )
                                {
                                    return 0;
                                }
                                else
                                    return -1;
                             }

                             // Vanaf ronde 20
                             if(getGame()->getPlays() >= 20)
                             {
                                //beide connectSuits zijn >10
                                if(getHand().getFirstCard()->getRank() > 10 && getHand().getSecondCard()->getRank() > 10)
                                {
                                    if (MiHand().miBetCheck() > 0.5)
                                    {
                                        return ( getGame()->getBlind() * 10);
                                    }
                                    else if( getGame()->getHighestBet() < getChips() / 12  )
                                    {
                                        return getGame()->getHighestBet() * 3;
                                    }
                                    else if( getGame()->getHighestBet() > getChips() / 12 && (getGame()->getHighestBet() < getChips() / 5 ) )
                                    {
                                        return 0;
                                    }
                                    else
                                        return -1;
                                }

                                //suited connects < 10
                                if (MiHand().miBetCheck() > 0.5)
                                {
                                    return ( getGame()->getBlind() * 3);
                                }
                                else if( getGame()->getHighestBet() > getChips() / 25 && (getGame()->getHighestBet() < getChips() / 15 ) )
                                {
                                    return 0;
                                }
                                else
                                    return -1;
                             }

                             //suited Not connected maar dicht bij elkaar
                             if( diffBetweenOrderedCards > 1 && diffBetweenOrderedCards < 5 )
                             {
                                if (MiHand().miBetCheck() > 0.5)
                                {
                                    return ( getGame()->getBlind() * 3);
                                }
                                else if( getGame()->getHighestBet() > getChips() / 30 && (getGame()->getHighestBet() < getChips() / 15 ) )
                                {
                                    return 0;
                                }
                                else
                                     return -1;
                             }

                             // willekeurig suited
                             if (MiHand().miBetCheck() > 0.4)
                             {
                                return 0;
                             }
                             else
                                return -1;
                          }
                    }
                }
                break;
            case 3:
                if(getHand().getFirstCard()->getRank() > 12 && getHand().getSecondCard()->getRank() > 12)
                {
                    if(getGame()->getHighestBet() > getChips()/4){ return (getChips());}

                    return ( getChips() / 4);
                }

                break;
            default:
                break;
            }
        }
        //ON FLOP
        else if( getTable()->isFlop() )
        {
            //POCKET STARTER
            if(getHand().getMyRank().handValue() >= THREE_OF_A_KIND)
            {
                return getChips();
            }
            else if(getHand().getMyRank().handValue() >= TWO_PAIR)
            {
                return 0;
            }
            else if(getGame()->getHighestBet() < getChips() / 6)
            {
                return 0;
            }
            else
                return -1;

            //FLUSH CHANCE
            if(getHand().getFirstCard()->getSuit() == getHand().getSecondCard()->getSuit())
            {
                // 4 suits op flop
                if((getTable()->getCommunityCards().at(0)->getSuit() && getTable()->getCommunityCards().at(1)->getSuit() == getHand().getFirstCard()->getSuit()) || (getTable()->getCommunityCards().at(0)->getSuit() && getTable()->getCommunityCards().at(2)->getSuit() == getHand().getFirstCard()->getSuit()) || (getTable()->getCommunityCards().at(2)->getSuit() && getTable()->getCommunityCards().at(1)->getSuit() == getHand().getFirstCard()->getSuit()))
                {
                    if(getGame()->getHighestBet() < getChips()/15)
                    {
                        return (getChips() / 5);
                    }
                    else if(getGame()->getHighestBet() < getChips()/5)
                    {
                        return 0;
                    }
                }
            }

            //ANDERS
            if(getHand().getMyRank().handValue() >= STRAIGHT)
            {
                return getChips();
            }
            else if(getHand().getMyRank().handValue() >= THREE_OF_A_KIND)
            {
                return 0;
            }
            else if(getGame()->getHighestBet() < getChips() / 10)
            {
                return 0;
            }
            else
                return -1;
        }
        //ON TURN
        else if( getTable()->isTurn() )
        {
            if(getHand().getMyRank().handValue() >= FLUSH)
            {
                return getChips();
            }
            else if(getHand().getMyRank().handValue() >= THREE_OF_A_KIND)
            {
                return 0;
            }
            else if(getGame()->getHighestBet() < getChips() / 10)
            {
                return 0;
            }
            else
                return -1;
        }
        //ON RIVER
        else
        {
            if(getHand().getMyRank().handValue() >= FLUSH)
            {
                return getChips();
            }
            else if(getChips() > getGame()->getHighestBet()-totalBet)
            {
                return 0;
            }
        }

}




}
