#ifndef GLOXMODELOBJECT_HPP_
#define GLOXMODELOBJECT_HPP_

/*
 * Author: jrahm
 * created: 2013/11/20
 * SloxModelObject.hpp: <description>
 */

#include "glox/GloxCommon.hpp"
#include "glox/GloxObject.hpp"

#include "slox/loader/SloxObjectMaterial.hpp"

namespace slox {

class SloxModelObject : public glox::GloxObject {

public:
    inline SloxModelObject( int disp ) : m_display_list( disp ) {}
    
    inline int getDisplayList() const { return m_display_list; }

    inline virtual void draw() const { glCallList( m_display_list ); }

    inline virtual ~SloxModelObject() {
    }
private:
    int m_display_list;
};

}

#endif /* GLOXMODELOBJECT_HPP_ */
