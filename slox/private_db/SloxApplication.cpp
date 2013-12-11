#include "slox/SloxApplication.hpp"

#include <cstdio>
#include <cstdlib>

namespace slox {

void SloxApplication::run( int argc, char** argv ) {
    SDL_Event event;
	memset( & event, 0, sizeof( event ) );
    bool run = true;
    
    /* Initialize the application */
    if( !this->initialize( argc, argv ) ) {
        fprintf( stderr, "Error initializing SloxApplication: %s\n", this->getError().c_str() );
        return ;
    }

    while( run ) {
        /* While we are continuing to
         * run */
        while( SDL_PollEvent( & event ) ) {
            /* Iterate through the events
             * and call the applications
             * raw evetn handler */
            this->onEvent( event );
        }

        /* Call the main meat of this
         * loop */
        run = this->loop( SDL_GetTicks() );
    }

    /* The cleanup should be handled by
     * the destructor */
}

}
