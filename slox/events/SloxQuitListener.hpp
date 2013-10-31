#ifndef SLOXQUITLISTENER_HPP_
#define SLOXQUITLISTENER_HPP_

/*
 * Author: jrahm
 * created: 2013/10/31
 * SloxQuitListener.hpp:
 *
 * An interface that is called when there
 * is a quit event in SDL
 */

#include "slox/SloxCommon.hpp"

namespace slox {

class SloxQuitListener {
public:
	/* Called when there was a quit event */
	virtual inline void onQuit( const SDL_QuitEvent& event ) { (void) event; };
};

}

#endif /* SLOXQUITLISTENER_HPP_ */
