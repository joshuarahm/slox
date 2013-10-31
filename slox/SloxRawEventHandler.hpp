#ifndef SLOXRAWEVENTLISTENTER_HPP_
#define SLOXRAWEVENTLISTENTER_HPP_

/*
 * Author: jrahm
 * created: 2013/10/31
 * SloxRawEventListenter.hpp:
 *
 * This is a raw event listening demultiplexer.
 * This will take many different SDL events
 * and route them to a list of event handlers
 */

#include <vector>

#include "slox/SloxCommon.hpp"

#include "slox/events/SloxKeyListener.hpp"
#include "slox/events/SloxQuitListener.hpp"

namespace slox {

class SloxRawEventHandler {
public:
	void onEvent( const SDL_Event& event );

	/* Add a key listener to this event handler */
	inline void addKeyListener( SloxKeyListener* listener ) {
		keyListeners.push_back( listener );
	}

	inline void addQuitListener( SloxQuitListener* listener ) {
		quitListeners.push_back( listener );
	}
	
private:
	std::vector<SloxKeyListener*> keyListeners;
	std::vector<SloxQuitListener*> quitListeners;
	
	// TODO: more to add
};

}

#endif /* SLOXRAWEVENTLISTENTER_HPP_ */
