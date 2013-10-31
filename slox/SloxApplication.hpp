#ifndef SLOXAPPLICATION_HPP_
#define SLOXAPPLICATION_HPP_

/*
 * Author: jrahm
 * created: 2013/10/30
 * SloxApplication.hpp: <description>
 */

#include <string>

#include <SDL/SDL.h>

namespace slox {

/* This is the base class for all applications
 * using the Slox framework */
class SloxApplication {
public:
    /* initializes the application. This function
     * is responsible for almost all of the initialization
     * of the application */
    virtual bool initialize(int argc, char** argv) = 0;
    
    /* This is called whenever there
     * is an event that is raised */
    virtual void onEvent( const SDL_Event& event ) = 0;

    /* This is called for every iteration
     * in the event loop. Returns
     * true if the application is to 
     * continue running */
    virtual bool loop( uint32_t ticks ) = 0;

    /* Runs this application. This
     * is the only implemented method
     * in this class */
    virtual void run( int argc=0, char** argv=NULL ) ;

    /* Clean up the application */
    virtual inline ~SloxApplication() {}

    /* Sets a useful error message for the
     * user to make it easier to debug problems */
    virtual inline void setError( const std::string& error ) {
        m_error = error;
    }

    /* Returns the error message */
    virtual inline const std::string& getError() const {
        return m_error;
    }

private:
    std::string m_error;
};

}

#endif /* SLOXAPPLICATION_HPP_ */
