#ifndef GLOXOBJECTMATERIAL_HPP_
#define GLOXOBJECTMATERIAL_HPP_

/*
 * Author: jrahm
 * created: 2013/11/20
 * glox::GloxObjectMaterial.hpp: <description>
 */

#include <string>
#include <algorithm>

#include "glox/GloxColor.hpp"
#include "glox/GloxTexture.hpp"

namespace slox {

class SloxObjectMaterial {
public:
    SloxObjectMaterial( const std::string name = ""
                      , const glox::GloxColor& ka = glox::GloxColor()
                      , const glox::GloxColor& kd = glox::GloxColor()
                      , const glox::GloxColor& ks = glox::GloxColor()
                      , float ns = 0
                      , const glox::GloxTexture& tex = glox::GloxTexture() ) :
        m_name( name ), m_Ka( ka ), m_Kd( kd ),
        m_Ks( ks ), m_Ns( ns ), m_tex( tex ) {}

    inline void setNs( float ns ) {
        m_Ns = ns;
    }

    inline void setTransparency( float trans ) {
        m_trans = trans;
    }

    inline void setKa( const glox::GloxColor& ka ) {
        m_Ka = ka;
    }

    inline void setKd( const glox::GloxColor& kd ) {
        m_Kd = kd;
    }

    inline void setKs( const glox::GloxColor& ks ) {
        m_Ks = ks;
    }

    inline void setName( const std::string name ) {
        m_name = name;
    }

    inline const std::string getName() const {
        return m_name ;
    }

    inline const glox::GloxColor& getKa() const {
        return m_Ka;
    }

    inline const glox::GloxColor& getKd() const {
        return m_Kd;
    }

    inline const glox::GloxColor& getKs() const {
        return m_Ks;
    }

    inline const glox::GloxTexture& getTexture() const {
        return m_tex;
    }

    inline float getNs() const {
        return m_Ns;
    }

    inline void setTexture( const glox::GloxTexture& tex ) {
        m_tex = tex;
    }

private:
    std::string m_name;
    glox::GloxColor m_Ka;
    glox::GloxColor m_Kd;
    glox::GloxColor m_Ks;

    float m_Ns;
    float m_trans;

    glox::GloxTexture m_tex;
};

}

#endif /* GLOXOBJECTMATERIAL_HPP_ */
