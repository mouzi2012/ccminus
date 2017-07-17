
OBJECTS = main.o min_source.o min_bnf.o min_syn.o min_terminal.o min_token.o hash_pool_manager.o hash_table.o string_pool.o
VPATH   = ./ccm ./ccm/min_common \
			./ccm/min_run ./ccm/min_run/parse/syntax ./ccm/min_run/parse/pool
			
CXX = g++ 
#CPPFLAGS = '-I/usr/local/include'
CXXFLAGS = -Wall -g -std=c++11
all:Test
Test:$(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(OBJECTS)
	
main.o:main.cxx
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $^
clean :
	-del $(OBJECTS) Test