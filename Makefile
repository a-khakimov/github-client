CC=g++
SOURCES=src/main.cpp \
	src/http/Param.cpp \
	src/http/Client.cpp \
	src/github/Repo.cpp

CCFLAGS=-Wall -std=c++11
LDFLAGS=-lcurl
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=github-client

all: $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) -c $(CCFLAGS) $< -o $@  $(INC)

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

.PHONY: all clean
