#ifndef SLOXKEYLISTENER_HPP_
#define SLOXKEYLISTENER_HPP_

/*
 * Author: jrahm
 * created: 2013/10/31
 * SloxKeyListener.hpp: 
 *
 * This is a class that is called
 * for key events
 */

#include "slox/SloxCommon.hpp"

namespace slox {

class SloxKeyListener {
public:
	/* Called when a key was pressed or
	 * repeated */
	virtual inline void onKeyDown( const SDL_KeyboardEvent& event ) { (void) event; }

	/* Called when a key was released */
	virtual inline void onKeyUp  ( const SDL_KeyboardEvent& event ) { (void) event; }
};

}

#endif /* SLOXKEYLISTENER_HPP_ */
