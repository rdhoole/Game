
CC = g++

CFLAGSOBJ = -std=c++11 -fPIC -pthread
CFLAGS = -std=c++11 -shared -pthread

INCLUDES = -I../include/linux/Irrlicht/ -I../include/linux/bullet/ -I../include/linux/bullet/LinearMath/

LDFLAGS = -L../lib/linux/bullet/ -L/usr/X11R6/ -L../lib/linux/Irrlicht/
MAC_LDFLAGS = -L../lib/mac/bullet/ -L../lib/mac/Irrlicht/

# ORDER MATTERS
LIBS = -lIrrlicht -lX11 -lXxf86vm -lz -lGL -lBulletDynamics -lBulletCollision -lLinearMath

MAC_LIBS = -lIrrlicht -fvisibility=hidden -framework cocoa -framework IOKit -framework OpenGL -framework AppKit -lz -lBulletDynamics -lBulletCollision -lLinearMath

SRCS = gameengine.cpp bulletdebugrender.cpp playerobject.cpp cameraobject.cpp charobject.cpp envobject.cpp gobject.cpp irrlichtstandard.cpp lightobject.cpp terrainobject.cpp keyconfig.cpp getobject.cpp addobject.cpp createnode.cpp actions.cpp world.cpp settings.cpp 

OBJS   = $(SRCS:.cpp=.o)

# Name of library is MAIN
MAIN = libGameEngine.so
#MAC_MAIN = gameengine.o # This causes a very very weird issue
MAC_MAIN = MyApp.app/Contents/MacOS/Main

BINDIR = ../lib/linux/
MAC_BINDIR = ../lib/mac/

#######################################

.PHONY: depend clean

default: linux

linux-test:
	$(CC) $(CFLAGS) $(INCLUDES) BulletTest.cpp -o $(BINDIR)BulletTest $(LDFLAGS) $(LIBS)

linux: $(MAIN)
mac: $(MAC_MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BINDIR)$(MAIN) $(OBJS) $(LDFLAGS) $(LIBS)

$(MAC_MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAC_BINDIR)$(MAC_MAIN) $(OBJS) $(MAC_LDFLAGS) $(MAC_LIBS)

.cpp.o:
	$(CC) $(CFLAGSOBJ) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o *~ $(BINDIR)$(MAIN) $(MAC_BINDIR)$(MAC_MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# LINE FOR makedepend
