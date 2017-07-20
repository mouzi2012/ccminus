SRCS =  main.cpp min_source.cpp min_bnf.cpp min_syn.cpp min_terminal.cpp min_token.cpp \
		  hash_pool_manager.cpp hash_table.cpp string_pool.cpp sim_tree.cpp singleton.cpp utils.cpp

VPATH   = ./ccm ./ccm/min_common \
			./ccm/min_run ./ccm/min_run/parse/syntax ./ccm/min_run/pool
			
CXX = g++ 
#CPPFLAGS = '-I/usr/local/include'
CXXFLAGS = -Wall -g -std=c++11

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

%.d: %.cxx
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(SRCS:.cpp=.d)

