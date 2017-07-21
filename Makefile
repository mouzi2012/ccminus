SRCS =  main.cpp min_source.cpp min_bnf.cpp min_syn.cpp min_terminal.cpp min_token.cpp \
		  hash_pool_manager.cpp hash_table.cpp string_pool.cpp sim_tree.cpp singleton.cpp utils.cpp

OBJECTS = $(SRCS:.cpp=.o)

VPATH   = ./ccm ./ccm/min_common \
			./ccm/min_run ./ccm/min_run/parse/syntax ./ccm/min_run/pool
			
CXX = g++ 
#CPPFLAGS = '-I/usr/local/include'
CXXFLAGS = -Wall -g -std=c++11

DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

all:Test
Test:$(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(OBJECTS)

clean :
	rm $(OBJECTS) Test

%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d
	$(COMPILE.cc) $< $(OUTPUT_OPTION) 
	$(POSTCOMPILE)

%.o : %.cxx
%.o : %.cxx $(DEPDIR)/%.d
	$(COMPILE.cc) $< $(OUTPUT_OPTION) 
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS))))

