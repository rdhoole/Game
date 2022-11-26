CC = g++

CFLAGS = -std=c++11
CFLAGSOBJ = -std=c++11

INCLUDES = -I../../src -I../../include/linux/Irrlicht/ -I../../include/linux/bullet/ -I../../include/linux/bullet/LinearMath/

LDFLAGS = -L../../lib/linux/ -L../../lib/linux/bullet/ -L/usr/X11R6/ -L../../lib/linux/Irrlicht/


# ORDER MATTERS
#LIBS = -lIrrlicht -lX11 -lXxf86vm -lz -lGL -lBulletDynamics -lBulletCollision -lLinearMath
LIBS = -lGameEngine -lIrrlicht -lBulletDynamics -lBulletCollision -lLinearMath

SRCS = main.cpp

OBJS   = $(SRCS:.cpp=.o)

# Name of library is MAIN
MAIN = main

BINDIR = ./

#######################################

.PHONY: depend clean

default: linux

linux: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BINDIR)$(MAIN) $(OBJS) $(LDFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGSOBJ) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# LINE FOR makedepend
