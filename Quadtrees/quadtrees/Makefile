.SUFFIXES:
.SUFFIXES: .o .cpp
#============================================================
TARGET	=  Quadtree

C_SOURCES =  quadtree.cpp main.cpp stack.cpp
C_OBJS     = quadtree.o main.o stack.o
MY_INCLUDES = quadtree.h stack.h

CCX = g++ 
CXXFLAGS = -g -std=c++11 -w 

OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV)

#============================================================
all: $(TARGET)

.o:.cpp	$(MY_INCLUDES)
	$(CCX)  -c  $(CXXFLAGS) $<  

$(TARGET) :   $(C_OBJS)
	$(CCX) $(CXXFLAGS)   $^ $(LIBDIRS)  $(LIBS) -o $@

# Implicit rules: $@ = target name, $< = first prerequisite name, $^ = name of all prerequisites
#============================================================

ALL_SOURCES = Makefile $(C_SOURCES) $(MY_INCLUDES)

NOTES =
%= otherstuff.np 

clean:
	rm -f $(TARGET) $(C_OBJS) core 

tar: $(ALL_SOURCES) $(NOTES)
	tar cvf $(TARGET).tar $(ALL_SOURCES)  $(NOTES)

$(TARGET).ps: $(ALL SOURCES)
	enscript -pcode.ps $(ALL_SOURCES)


