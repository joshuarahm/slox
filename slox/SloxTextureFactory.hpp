#ifndef SLOXTEXTUREFACTORY_HPP_
#define SLOXTEXTUREFACTORY_HPP_

/*
 * Author: jrahm
 * created: 2013/10/30
 * SloxTextureFactory.hpp: <description>
 */

#ifndef NO_OPENGL

#include <string>
#include <GL/gl.h>
#include "slox/SloxCommon.hpp"
#include <vector>

#include <SDL/SDL_image.h>

namespace slox {

/* has dependencies on OpenGL */
class SloxTextureFactory {
public:
	inline SloxTextureFactory( ) {
		m_path.push_back( "." );
		m_path.push_back( "" );
	}

	/* returns 0 if ok, 1 if warning, -1 if error */
    int readBitmapFile( const char* filename, unsigned int* texture ) ;

    int readImageFile( const char* filename, unsigned int* texture ) ;

    const std::string& getMessage() ;

	inline void addToPath( const char* path ) {
		m_path.push_back( path );
	}

private:
	int getFileFromPath( const char* basename, std::string& into );

	std::vector<std::string> m_path;

	std::string m_message;
};

}

#else
#warn "SloxTextureFactory is not available when compiling with -D NO_OPENGL"
#endif

#endif /* SLOXTEXTUREFACTORY_HPP_ */
