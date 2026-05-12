CXX=g++
CXXFLAGS=-std=c++17

OATPP_SWAGGER_INCLUDE = /usr/local/include/oatpp-1.3.0/oatpp-swagger
OATPP_INCLUDE_LIB = /usr/local/include/oatpp-1.3.0/oatpp
OATPP_INCLUDE = -I src -I $(OATPP_INCLUDE_LIB) -I $(OATPP_SWAGGER_INCLUDE)

LINKFLAGS_LOCAL = -L /usr/local/lib/oatpp-1.3.0
LINKFLAGS_APP = $(LINKFLAGS_LOCAL) -loatpp-swagger -loatpp

SRC_DIR_SERVER = src/server
SRC_DIR_MODEL = src/model
SRC_DIR_SERVICE = src/service

PROGRAM_SERVER = gameServer

.PHONY: all clean server

all: server

clean:
	rm -rf $(PROGRAM_SERVER) *.o *.gcov *.gcda *.gcno results.coverage coverage doxygen/html obj bin *~

server: $(PROGRAM_SERVER)

$(PROGRAM_SERVER):
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_SERVER) $(OATPP_INCLUDE) \
	$(SRC_DIR_SERVER)/*.cpp \
	$(SRC_DIR_MODEL)/*.cpp \
	$(SRC_DIR_SERVICE)/*.cpp \
	$(LINKFLAGS_APP)
	