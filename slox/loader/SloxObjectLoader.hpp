#ifndef GLOXOBJECTLOADER_HPP_
#define GLOXOBJECTLOADER_HPP_

/*
 * Author: jrahm
 * created: 2013/11/20
 * SloxObjectLoader.hpp: <description>
 */

#include "slox/loader/SloxModelObject.hpp"
#include "slox/SloxTextureFactory.hpp"

#include <vector>
#include <fstream>
#include <iostream>
#include <cerrno>

namespace slox {

/* This class is used to load obj files and
 * return an object that when drawn will appear
 * as the object depicted by the obj file 
 * loaded */
class SloxObjectLoader {
public:
	inline SloxObjectLoader( SloxTextureFactory* textureFactory = NULL ) {
		m_path.push_back( "." );
		m_path.push_back( "" );
		m_texture_factory = textureFactory;
	}

	inline void setTextureFactory( SloxTextureFactory* factory ) {
		m_texture_factory = factory;
	}

    /* loads an object from an input stream.
     * The stream should have the contents of an
     * obj file */
    SloxModelObject* loadObjectFromStream( std::istream& input );

    /* Loads an object from a file, this
     * is a humble wrapper around the loadOBjectFromStream
     * declared above that opens the file with a
     * standard istream */
    inline SloxModelObject* loadObjectFromFile( const std::string& filename ) {
        std::ifstream stream;
        SloxModelObject* ret = NULL;

    	/* Try to open the stream, load the object
     	* from that stream and close the
     	* stream */
		if( openFileFromPath( filename.c_str(), stream ) ) {
			object_loader_reason = filename + ": not found on path";
			return NULL;
		}

        ret = loadObjectFromStream( stream );
        stream.close();
        return ret;
    }

    /* If the object loading fails and returns
     * NULL, calling this function will return
     * a string describing the reason */
    const char* getReason() const ;

	/* Add a path to the path variable so
	 * the factory will look in this folder
	 * for a texture */
	inline void addToPath( const char* path ) {
		m_path.push_back( path );
	}
private:
	void loadMaterial( const char* file );

	/* Returns the file from the path */
	int openFileFromPath( const char* basename, std::ifstream& into );

	/* This is a string that describes the current
 	* filename that is being parsed. 
 	*
 	* This name will take the name of *.obj or *.mtl
 	*/
	const char* object_loader_filename;
	
	/*
 	* This is a string that depicts the reason
 	* for failure. This should not be accessed
 	* directly, use SloxObjectLoader::getReason()
 	* instead, I'm just being lazy */
	std::string object_loader_reason;

	/* 
	 * The places on the filesystem where this object
	 * loader will look for objects to load
	 */
	std::vector< std::string > m_path;

	/* The texture factory used to load
	 * the textures into the program */
	SloxTextureFactory* m_texture_factory;
};

}

#endif /* GLOXOBJECTLOADER_HPP_ */
