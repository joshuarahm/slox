#include <vector>
#include <map>
#include <sstream>
#include <cstdio>
#include <fstream>

#include "slox/loader/SloxObjectLoader.hpp"

#include "glox/GloxScopedAttributes.hpp"
#include "glox/GloxScopedBegin.hpp"
#include "glox/GloxPoint.hpp"
#include "glox/GloxNormal.hpp"
#include "glox/GloxCommon.hpp"
#include "glox/GloxTextureFactory.hpp"
#include <sys/stat.h>

using namespace std;
using namespace glox;

namespace slox {

int SloxObjectLoader::openFileFromPath( const char* basename, std::ifstream& into ) {
	struct stat st;
	char buf[4096];
	into.clear();
	for( vector<string>::iterator itr = m_path.begin(); itr < m_path.end(); ++ itr ) {
		snprintf( buf, 4096, "%s/%s", (*itr).c_str(), basename );
		if( ! stat( buf, & st ) ) {
			into.open( buf, ios::in );
			return 0;
		}
	}

	/* Nothing was found */
	return 1;
}

/* The reason the loading failed
 * if it did */
std::string object_loader_reason;

/* The map of material names to their
 * respective materials */
static map< string, SloxObjectMaterial > materials;

/* The current line number of the stream */
int linenum = 0;

/* The current filename being parsed */
const char* object_loader_filename = NULL;

/* Helper function that trims the whitespace from
 * a string */
static inline std::string &trim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
};

/* Simple function that returns the reason
 * why the loader failed */
const char* SloxObjectLoader::getReason() const {
    return object_loader_reason.c_str();
}

/* Typedef a texture point to a pair
 * of floats */
typedef pair<float,float> TexPointT;

/* Read n number of floats into a float
 * array */
void p_read_n_floats__( const char* line, float* floats, size_t n ) {
    stringstream linestream( line );

    for( size_t i = 0; i < n; ++ i ) {
        if( linestream.eof() ) throw "Premature EOF while reading floats!";
        linestream >> floats[i];
    }
}

/* read a point in the for "%f %f %f" from a
 * line */
inline GloxPointf p_read_point__( const char* line ) {
    float xyz[3];
    p_read_n_floats__( line, xyz, 3 );
    return GloxPointf( xyz[0], xyz[1], xyz[2] );
}

/* Read a color in the save format as mentioned above */
inline GloxColor p_read_color__( const char* line ) {
    float xyz[3];
    p_read_n_floats__( line, xyz, 3 );
    return GloxColor( xyz[0], xyz[1], xyz[2] );
}

/* read a normal in the same format as mentioned
 * above */
inline GloxNormal<> p_read_normal__( const char* line ) {
    float xyz[3];
    p_read_n_floats__( line, xyz, 3 );
    return GloxNormal<>( xyz[0], xyz[1], xyz[2] );
}

/* Read a texture point in the form
 * "%f %f" as above */
inline TexPointT p_read_tex_point__( const char* line ) {
    float xy[2];
    p_read_n_floats__( line, xy, 2 );
    return TexPointT( xy[0], xy[1] );
}

/* Have OpenGL set the material to the
 * material as referenced by 'name'
 */
void setMaterial( const char* name ) {
    if( materials.find( name ) == materials.end() ) {
        cerr << "Unable to set the material " << name << "; The material was never loaded\n" << endl;
        throw "Unable to set material; never loaded";
    }

    const SloxObjectMaterial& material = materials[ name ];
    float fvec[4];
    material.getKa().toVector( fvec, 4 );
    cout << "Material KA: " << material.getKa().toString() << endl;
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT  ,fvec);
    material.getKd().toVector( fvec, 4 );
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE  ,fvec);
    material.getKs().toVector( fvec, 4 );
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR ,fvec);
    fvec[0] = material.getNs();
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS, &fvec[0]);

    cout << "Reading Texture with id of: " << material.getTexture().getId() << endl;
    if( material.getTexture().getId() > 0 ) {
        glEnable( GL_TEXTURE_2D );
        material.getTexture().bind();
    } else {
     glDisable( GL_TEXTURE_2D );
    }
}

/* Load a material from the file 'file' */
void SloxObjectLoader::loadMaterial( const char* file ) {
    ifstream instream;
    const char* oldobject_loader_filename = object_loader_filename;
    object_loader_filename = file;

    string line;
    string word;

    SloxObjectMaterial* material = NULL;

    if( openFileFromPath( file, instream ) ) {
        throw "Unable to open material file!";
    }

    linenum = 0;
    while( ! instream.eof() ) {
        getline( instream, line ) ;
        ++ linenum;
        stringstream linestream( line );
        linestream >> word;
        if( word == "newmtl" ) {
            linestream >> word;
            material = & materials[ word ];
            material->setName( word );
        } else if ( material == NULL ) {
            /* Do Nothing */
        } else if ( ! line.compare( 0, 2, "Ka" ) ) {
            material->setKa( p_read_color__( line.c_str() + 2 ) );
        } else if ( ! line.compare( 0, 2, "Kd" ) ) {
            material->setKd( p_read_color__( line.c_str() + 2 ) );
        } else if ( ! line.compare( 0, 2, "Ks" ) ) {
            material->setKs( p_read_color__( line.c_str() + 2 ) );
        } else if ( ! line.compare( 0, 2, "Ns" ) ) {
            float tmp;
            linestream >> tmp;
            material->setNs( tmp );
        } else if( word == "map_Kd" ) {
            linestream >> word;
			unsigned int tex;
			int ret;

            if ( word[0] == '/' ) {
                cerr << "Warning: absolute path being used for texture!" << endl ;
                exit( 1 );
            }

            ret = m_texture_factory->readImageFile( word.c_str(), &tex );
            if( ret < 0 ) {
                cerr << "Can't read texture: " << m_texture_factory->getMessage() << endl;
                throw "Unable to open texture file!";
            }
			GloxTexture tmp( tex );
            cout << "Crated texture with id of: " << tmp.getId() << endl;
            material->setTexture( tmp );
        }
    }

    instream.close();
    object_loader_filename = oldobject_loader_filename;
}

SloxModelObject* SloxObjectLoader::loadObjectFromStream( istream& input ) {
    int display_list = glGenLists( 1 );
    vector< GloxPointf > verts;
    vector< GloxNormal<> > norms;
    vector< TexPointT  > tex_points;

    string line;

    glNewList( display_list, GL_COMPILE );
    GloxScopedAttributes p_gsa__( GL_TEXTURE_BIT );

    try {
        while( ! input.eof() ) {
            getline( input, line );
			if( input.fail() ) {
				/* If we fail to read, break */
				break ;
			}
            trim( line );

            /* handle the case for points/normals/texture points */
            if( ! line.compare( 0, 2, "v " ) ) {
                verts.push_back( p_read_point__( line.c_str() + 2 ) );
            } else if ( ! line.compare( 0, 2, "vn" ) ) {
                norms.push_back( p_read_normal__( line.c_str() + 2 ) );
            } else if ( ! line.compare( 0, 2, "vt" ) ) {
                tex_points.push_back( p_read_tex_point__( line.c_str() + 2 ) );
            }

            /* build the face */
            else if( line[0] == 'f' ) {
                const char* lineptr = line.c_str() + 1;
                { GloxScopedBegin p_gsb__( GL_POLYGON );
                    stringstream linestream( lineptr );
                    std::string word;
                    while( ! linestream.eof() ) {
                        unsigned int Kv = 0;
                        unsigned int Kt = 0;
                        unsigned int Kn = 0;

                        linestream >> word;

                        if( ! (sscanf( word.c_str(), "%u/%u/%u", &Kv, &Kt, &Kn ) == 3 ||
                               sscanf( word.c_str(), "%u//%u", &Kv, &Kn ) == 2 ||
                               sscanf( word.c_str(), "%u", &Kv ) == 1 ) ){
                               throw "Invalid facet!";
                        }

                        if ( Kv > verts.size() ) throw "Vertex out of range!";
                        if ( Kn > norms.size() ) throw "Normal out of range!";
                        if ( Kt > tex_points.size() ) throw "Texture out of range!";

                        float arr[4];
                        cout << "face (" << Kv << ", " << Kt << ", " << Kn  << ")" << endl;
                        if ( Kt ) {
                            arr[0] = tex_points[Kt-1].first;
                            arr[1] = tex_points[Kt-1].second;
                            glTexCoord2fv( arr );
                        } 
                        if( Kn ) {
                            norms[Kn - 1].plot();
                        } if( Kv ) {
                            verts[Kv - 1].plot();
                        }

                    }} /* End GloxScopedBegin */

            } else {
                stringstream linestream( line );
                string word;
                linestream >> word;

                if( word == "usemtl" ) {
                    /* use the material in the next word */
                    linestream >> word;
                    setMaterial( word.c_str() );
                } else if ( word == "mtllib" ) {
                    linestream >> word;
                    loadMaterial( word.c_str() );
                }
            }

        }
    } catch( const char * reason ) {
        glEndList();
        char buf[512];
        snprintf( buf, 512, "%s file: %s line: %d", reason, object_loader_filename,  linenum );
        object_loader_reason = buf;
        object_loader_filename = NULL;
        return NULL;
    }

    glEndList();
    return new SloxModelObject( display_list );
}

}
