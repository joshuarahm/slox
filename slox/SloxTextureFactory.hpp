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

namespace slox {

/* has dependencies on OpenGL */
class SloxTextureFactory {
public:

    static int readBitmapFile( const char* filename, unsigned int* texture ) ;

    static const std::string& getMessage() ;
};

}

#else
#warn "SloxTextureFactory is not available when compiling with -D NO_OPENGL"
#endif

#endif /* SLOXTEXTUREFACTORY_HPP_ */
