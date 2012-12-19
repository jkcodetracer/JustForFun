CPPFLAGS = -Wall -DCTDEBUG
SRCDIRS = ./

SRCEXTS = .c
HDREXTS = .h

CFLAGS = -g -O2

SHELL = /bin/sh

SOURCES = $(foreach, d,$(SRCDIRS), $(wildcard $(addprefix $(d)/*,$(SRCEXTS))))

HEADERS = $(foreach, d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*, $(HDREXTS))))
OBJS = $(addprefix .o, $(basename $(SOURCES)))
DEPS = $(OBJS: .o=.d)
DEPEND = gcc 
DEPEND.d = $(subst -g ,, $(DEPEND))

.PHONY: all objs
.SUFFIXES:

all: a.out

%.d:%.c
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

objs:$(OBJS)

%.o:%.c
	gcc -c $< -o $@
