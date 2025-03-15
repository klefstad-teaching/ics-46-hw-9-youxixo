CXX = g++
CXXFLAGS = -std=c++11 -Wall

LADDER_SRCS = src/ladder.cpp src/ladder_main.cpp
DIJKSTRA_SRCS = src/dijkstras.cpp src/dijkstras_main.cpp

all: ladder dijkstras

ladder: $(LADDER_SRCS)
	$(CXX) $(CXXFLAGS) $(LADDER_SRCS) -o ladder

dijkstras: $(DIJKSTRA_SRCS)
	$(CXX) $(CXXFLAGS) $(DIJKSTRA_SRCS) -o dijkstras

clean:
	rm -f ladder dijkstras
