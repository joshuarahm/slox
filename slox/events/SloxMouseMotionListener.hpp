#ifndef SLOXMOUSEMOTIONLISTENER_HPP_
#define SLOXMOUSEMOTIONLISTENER_HPP_

/*
 * Author: jrahm
 * created: 2013/11/01
 * SloxMouseMotionListener.hpp: <description>
 */

#include "slox/SloxCommon.hpp"

namespace slox {
	
/* A class that listens for mouse motion */
class SloxMouseMotionListener {
public:
	/* Called when the mouse is moved */
	virtual inline void onMouseMoved( const SDL_MouseMotionEvent& event ) {
		(void) event;
	};
};
	
}

#endif /* SLOXMOUSEMOTIONLISTENER_HPP_ */
