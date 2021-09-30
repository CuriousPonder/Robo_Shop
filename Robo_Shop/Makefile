# Makefile for ROBO
CXXFLAGS += --std=c++11
LDFLAGS = -L/usr/local/lib -lXext -lm -Wl,-Bsymbolic-functions -lfltk_images -lfltk -lX11

all: robo

debug: CXXFLAGS += -g
debug: robo

rebuild: clean robo


robo: robo_shop.cpp
	$(CXX) $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o robo robo_shop.cpp $(LDFLAGS)

clean:
	-rm -f *.o robo



