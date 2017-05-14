CXX = g++

CFLAGS = -std=c++11
PFLAGS = -DPRINT
DFLAGS = -g

LFLAGS = -lpthread -lGLU -lglut -lGL -lglui -lm

SRCDIR = src
OBJDIR = obj
INCDIR = inc
DEPDIR = deps

INCPATH = -I$(INCDIR)

OTMP = $(patsubst %.cpp,%.o,$(wildcard $(SRCDIR)/*.cpp))
DEPS = $(patsubst %.o,$(DEPDIR)/%.d,$(OTMP))
SRCS = $(wildcard $(SRCDIR)/*.cpp)
INCLUDES = $(wildcard $(INCDIR)/*.h)
OBJS = $(subst $(SRCDIR)/,$(OBJDIR)/,$(SRCS:.cpp=.o))

MAIN = a.out

execute: init $(MAIN)
	./$(MAIN) $(num_thread)

debug: CFLAGS += $(DFLAGS)
debug: init $(MAIN)
	./$(MAIN) $(num_thread)

print: CFLAGS += $(PFLAGS)
print: init $(MAIN)
	./$(MAIN) $(num_thread)

init:
	mkdir -p $(DEPDIR)
	mkdir -p $(OBJDIR)

-include $(DEPS)
	
$(MAIN): $(OBJS)
	$(CXX) $(CFLAGS) -o $(MAIN) $(OBJS) $(LFLAGS) -L$(SRCDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) $(INCPATH) -o $@ -c $<
	$(CXX) -MM -MT $(OBJDIR)/$*.o $(CFLAGS) $(INCPATH) $(SRCDIR)/$*.cpp > $(DEPDIR)/$*.d
	@cp -f $(DEPDIR)/$*.d $(DEPDIR)/$*.d.tmp
	@sed -e 's/.*://' -e 's/\\\\$$//' < $(DEPDIR)/$*.d.tmp | fmt -1 | \
        sed -e 's/^ *//' -e 's/$$/:/' >> $(DEPDIR)/$*.d
	@rm -f $(DEPDIR)/$*.d.tmp

clean:
	$(RM) $(OBJDIR)/*.o $(DEPDIR)/*.d *~ $(MAIN)