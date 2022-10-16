//#include "king_of_aces.h"
#include "miguel.h"
#include "game.h"

namespace PXL2022
{
/*
const char * Miguel::getName() const
{
    return "Miguel";
}
*/

int Miguel::willYouRaise( unsigned int totalBet )
{
	PokerRank mijnHandRank = getRank();
    if( getTable()->isPreFlop() ) //PRE FLOP
	{
        //SUITED hands
		if( getHand().getFirstCard()->getSuit() == getHand().getSecondCard()->getSuit() )
        {
			int diffBetweenOrderedCards = mijnHandRank.getHand().at(0) - mijnHandRank.getHand().at(1);
			if( diffBetweenOrderedCards == 1 || diffBetweenOrderedCards == 13 )
			{ //suited connected

                switch (instance) {
                case 0:


                    break;
                case 1:

                    break;
                case 2:

                    break;
                case 3:

                    break;
                default:
                    break;
                }

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
			}

            //suited Not connected maar dicht bij elkaar
            if( diffBetweenOrderedCards > 1 && diffBetweenOrderedCards < 5 )
            {
                /*  !!! HOE MOET IK HIER BEREKENEN WAT MIJN POSITIE IS???
                if( getGame()->getPlayers() - getGame()->getPlayerLocation() < 2)
                {

                }
                */
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

        } // einde suited

        //POCKETS
		if( getHand().getFirstCard()->getRank() == getHand().getSecondCard()->getRank() )
		{ //1 pair to start

            // eerste 60 rondes
            if(getGame()->getPlays() < 60)
            {
                //pocket >10
                if(getHand().getFirstCard()->getRank() > 10)
                {
                    if (MiHand().miBetCheck() > 0.5)
                    {
                        return ( getGame()->getBlind() * 8);
                    }
                    else if( getGame()->getHighestBet() < getChips() / 12  )
                    {
                        return getGame()->getHighestBet() * 2;
                    }
                    else if( getGame()->getHighestBet() > getChips() / 12 && (getGame()->getHighestBet() < getChips() / 5 ) )
                    {
                        return 0;
                    }
                    else
                        return -1;
                }

                //pocket <= 10
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

            // vanaf ronde 60
            if(getGame()->getPlays() >= 60)
            {

                //pocket KK of AA
                if(getHand().getFirstCard()->getRank() > 12){ return getChips();}

                //pocket >10
                if(getHand().getFirstCard()->getRank() > 10)
                {
                    if (MiHand().miBetCheck() > 0.5)
                    {
                        return ( getGame()->getBlind() * 12);
                    }
                    else if( getGame()->getHighestBet() < getChips() / 15  )
                    {
                        return getGame()->getHighestBet() * 2;
                    }
                    else if( getGame()->getHighestBet() > getChips() / 12 && (getGame()->getHighestBet() < getChips() / 5 ) )
                    {
                        return 0;
                    }
                    else
                        return -1;
                }

                //pocket <= 10
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


            return -1;
		}

		int diffBetweenOrderedCards = mijnHandRank.getHand().at(0) - mijnHandRank.getHand().at(1);
		if( diffBetweenOrderedCards == 1 || diffBetweenOrderedCards == 13 )
		{ //unsuited connected
			return ( getGame()->getBlind() * 3 ) - totalBet; //max 3x blind and fold otherwise
		}
		if( totalBet > getGame()->getBlind() * 2 )
		{
			return -1;
		}
		return 0;
	}
	else if( getTable()->isFlop() )
	{ //on flop

 //


        //POCKETS
        if( getHand().getFirstCard()->getRank() == getHand().getSecondCard()->getRank() )
        {
            if(getHand().getFirstCard()->getRank() > 10)
            {
                if(getHand().getMyRank().handValue() >= TWO_PAIR){ return getChips();}
            }
            else if(getHand().getMyRank().handValue() >= TWO_PAIR)
            {
                if (MiHand().miBetCheck() > 0.5)
                {
                    return ( getChips() / 10);
                }
                else if( (getGame()->getPlays() < 60) && getGame()->getHighestBet() > getChips() / 20 && (getGame()->getHighestBet() < getChips() / 10 ) )
                {
                    return getGame()->getHighestBet() * 2;
                }
                else if(getHand().getMyRank().handValue() >= THREE_OF_A_KIND)
                {
                    if (MiHand().miBetCheck() > 0.5)
                    {
                        return ( getChips() / 10);
                    }
                    else if( (getGame()->getPlays() < 60) && getGame()->getHighestBet() > getChips() / 20 && (getGame()->getHighestBet() < getChips() / 10 ) )
                    {
                        return getGame()->getHighestBet() * 2;
                    }
                    else
                        return 0;
                }
            }
            return -1;
        }

        //SUITEDS
        if( getHand().getFirstCard()->getSuit() == getHand().getSecondCard()->getSuit() )
        {
            if(getHand().getFirstCard()->getRank() > 10 || getHand().getSecondCard()->getRank() > 10)
            {
                if(getHand().getMyRank().handValue() >= FLUSH){ return getChips();}
            }
            //else if(getGame().){}
            else if(getHand().getMyRank().handValue() >= TWO_PAIR)
            {
                if (MiHand().miBetCheck() > 0.5)
                {
                    return ( getChips() / 10);
                }
                else if( (getGame()->getPlays() < 60) && getGame()->getHighestBet() > getChips() / 20 && (getGame()->getHighestBet() < getChips() / 10 ) )
                {
                    return getGame()->getHighestBet() * 2;
                }
                else
                    return 0;
            }

            if(getHand().getMyRank().handValue() >= THREE_OF_A_KIND)
            {
                if (MiHand().miBetCheck() > 0.5)
                {
                    return ( getChips() / 10);
                }
                else if( (getGame()->getPlays() < 60) && getGame()->getHighestBet() > getChips() / 20 && (getGame()->getHighestBet() < getChips() / 10 ) )
                {
                    return getGame()->getHighestBet() * 2;
                }
                else
                    return 0;
             }
            return -1;
        }

		talkSmack();
		return 0;
	}
	else if( getTable()->isTurn() )
	{ //on turn

        if(getHand().getMyRank().handValue() >= THREE_OF_A_KIND)
        {
            if( getHand().getFirstCard()->getRank() > 10 || getHand().getSecondCard()->getRank() >10 )
            {
                return ( getChips() / 3);
            }
            else
                return 0;
        }

        if (MiHand().miBetCheck() > 0.5)
        {
            return 0;
        }
        return -1;
	}
	else
	{ //on river

        if(getHand().getMyRank().handValue() > THREE_OF_A_KIND)
        {
            if( getHand().getFirstCard()->getRank() > 10 || getHand().getSecondCard()->getRank() >10 )
            {
                return ( getChips() );
            }
            else
                return 0;
        }

        if (MiHand().miBetCheck() > 0.5)
        {
            return 0;
        }
        return -1;
    }

		return 0;
	}
}

void PXL2022::Miguel::talkSmack()
{
    std::cout << "You are all losers !!! My stack is " << getChips() << std::endl;
}

