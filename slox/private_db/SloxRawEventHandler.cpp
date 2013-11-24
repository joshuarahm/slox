#include "slox/SloxRawEventHandler.hpp"

using namespace std;

namespace slox {

void SloxRawEventHandler::onEvent( const SDL_Event& event ) {
	switch( event.type ) {
	case SDL_VIDEORESIZE:
		for( vector<SloxResizeListener*>::iterator itr = resizeListeners.begin();
			itr != resizeListeners.end(); ++ itr ) {
			(*itr)->onResize( event.resize );
		}
		break;
	case SDL_KEYDOWN:
		for( vector<SloxKeyListener*>::iterator itr = keyListeners.begin();
			itr != keyListeners.end(); ++ itr ) {
			(*itr)->onKeyDown( event.key );
		}
		break;

	case SDL_KEYUP:
		for( vector<SloxKeyListener*>::iterator itr = keyListeners.begin();
			itr != keyListeners.end(); ++ itr ) {
			(*itr)->onKeyUp( event.key );
		}
		break;

	case SDL_QUIT:
		for( vector<SloxQuitListener*>::iterator itr = quitListeners.begin();
			itr != quitListeners.end(); ++ itr ) {
			(*itr)->onQuit( event.quit );
		}
	case SDL_MOUSEMOTION:
		for( vector<SloxMouseMotionListener*>::iterator itr = mouseMotionListeners.begin();
			itr != mouseMotionListeners.end(); ++ itr ) {
			(*itr)->onMouseMoved( event.motion );
		}
		
	}
}

}
