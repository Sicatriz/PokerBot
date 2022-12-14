#include <iostream>
#include <string.h>

#include "shootout.h"
#include "tournament.h"
#include "king_of_aces.h"
#include "bart.h"
#include "miguel.h"

using namespace std;

int main( int argumentCount, char * argumentVector[] )
{
	srand( (unsigned int) time( NULL ) );
	Tournament tour;

	for( unsigned char i = 0 ; i < 4 ; i++ )
	{
        tour.registerPlayer( new PXL2022::KingOfAces( i ), CUSTOM );
        //tour.registerPlayer( new PXL2022::Bart( i ), PXL_2021 );
        tour.registerPlayer( new PXL2022::Miguel( i ), PXL_2022 );
    }

   const Player * winnaar = tour.start();

    if( argumentCount > 1 && ( strcmp( argumentVector[argumentCount-1], "stats" ) == 0 ) )
    {
        runStatistics( tour, 100 );
    }
    else
    {
        /*const Player * winnaar = */tour.start();
    }




return( 0 );
}
