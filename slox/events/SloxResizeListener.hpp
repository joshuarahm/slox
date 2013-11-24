#ifndef SLOXRESIZELISTENER_HPP_
#define SLOXRESIZELISTENER_HPP_

/*
 * Author: jrahm
 * created: 2013/11/01
 * SloxResizeListener.hpp: <description>
 */

#include "slox/SloxCommon.hpp"

namespace slox {

class SloxResizeListener {
public:
	inline virtual void onResize( const SDL_ResizeEvent& event ) { (void)event; }
};

}

#endif /* SLOXRESIZELISTENER_HPP_ */
