#ifndef SLOXFUNCTIONQUITLISTENER_CPP_
#define SLOXFUNCTIONQUITLISTENER_CPP_

/*
 * Author: jrahm
 * created: 2013/10/31
 * SloxFunctionQuitListener.cpp:
 *
 * Simple implementation of QuitListener
 * that just takes a function as an argument 
 */

#include "slox/events/SloxQuitListener.hpp"

namespace slox {

class SloxFunctionQuitListener : public SloxQuitListener {
public:
	inline SloxFunctionQuitListener( void (*func)( const SDL_QuitEvent& evt ) ) {
		m_function_ptr = func;
	}

	virtual inline void onQuit( const SDL_QuitEvent& event ) {
		m_function_ptr( event );
	}

private:
	void (*m_function_ptr)( const SDL_QuitEvent& evt );
};

}



#endif /* SLOXFUNCTIONQUITLISTENER_CPP_ */
