Q         = q

CC        = clang
CXX       = clang++
CXXARGS   = -I./include
CXXFLAGS  = -std=c++17 -Wall -Wextra

include src/sources.mk

PREFIX   ?= /usr/local
BINDIR   ?= $(PREFIX)/bin
DESTDIR  ?=

.PHONY : all clean install

all : $(Q)
	
$(Q): src/Q.o $(OBJS)
	$(CXX) $(CXXARGS) $(CXXFLAGS) -o $@ $^ 

%.o: %.cpp
	$(CXX) $(CXXARGS) $(CXXFLAGS) -o $@ -c $<

%.o: %.c
	$(CC)  $(CXXARGS) $(CXXFLAGS) -o $@ -c $<

clean :
	rm -f $(Q) $(OBJS)

install : $(Q)
	mkdir -p $(DESTDIR)$(BINDIR)
	install -m 755 $(Q) $(DESTDIR)$(BINDIR)/$(Q)
