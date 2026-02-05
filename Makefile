APP       = q

CC        = clang
CXX       = clang++
CXXARGS   = -I./include
CXXFLAGS  = -std=c++17 -Wall -Wextra

include src/sources.mk
include src/baseEncoding/sources.mk

include src/dns/sources.mk
include src/dns/EDNS0/sources.mk
include src/dns/RR/sources.mk
include src/dns/RR/DANE/sources.mk
include src/dns/RR/SEC/sources.mk
include src/dns/RR/SSHFP/sources.mk
include src/dns/RR/SVC/sources.mk

include src/ds/sources.mk
include src/net/sources.mk
include src/view/sources.mk

PREFIX   ?= /usr/local
BINDIR   ?= $(PREFIX)/bin
DESTDIR  ?=

.PHONY : all clean install

all : $(APP)
	
$(APP): $(OBJS)
	$(CXX) $(CXXARGS) $(CXXFLAGS) -o $@ $^ 

%.o: %.cpp
	$(CXX) $(CXXARGS) $(CXXFLAGS) -o $@ -c $<

%.o: %.c
	$(CC)  $(CXXARGS) $(CXXFLAGS) -o $@ -c $<

clean :
	rm -f $(APP) $(OBJS)

install : $(APP)
	mkdir -p $(DESTDIR)$(BINDIR)
	install -m 755 $(APP) $(DESTDIR)$(BINDIR)/$(APP)
