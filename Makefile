CPPC?=g++
AR?=ar
OPTFLAGS?=-g3 -ggdb
CFLAGS= -Wall -Wextra -I. $(OPTFLAGS) -D DEBUG_LEVEL_TRACE -Islox -I../glox
LDFLAGS=
OBJECTS=obs/SloxObjectLoader.o obs/SloxApplication.o obs/SloxRawEventHandler.o obs/SloxTextureFactory.o
BINARY=libslox.a
all: setup $(OBJECTS)
	$(AR) -r $(BINARY) $(OBJECTS)

setup:
	mkdir -p obs/

clean:
	- rm -rf obs $(BINARY)

obs/SloxObjectLoader.o: ./slox/loader/private_db/SloxObjectLoader.cpp \
                            slox/loader/SloxObjectLoader.hpp
	$(CPPC) $(CFLAGS) -o $@ -c $<

obs/SloxApplication.o: ./slox/private_db/SloxApplication.cpp \
                            slox/SloxApplication.hpp
	$(CPPC) $(CFLAGS) -o $@ -c $<

obs/SloxRawEventHandler.o: ./slox/private_db/SloxRawEventHandler.cpp \
                            slox/SloxRawEventHandler.hpp
	$(CPPC) $(CFLAGS) -o $@ -c $<

obs/SloxTextureFactory.o: ./slox/private_db/SloxTextureFactory.cpp \
                            slox/SloxTextureFactory.hpp
	$(CPPC) $(CFLAGS) -o $@ -c $<

