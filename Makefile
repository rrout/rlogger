DESTDIR=../../
OUT_DIR=./lib
STATIC=librlogger.a

CC = g++
CFLAGS = -Wall -Winline -pipe -DLINUX -I./hdr

LDFLAGS = -L../../../lib
LIBS    = -lpthread 

SRC = src/rlogger.cc

OBJ = $(SRC:.cc=.o)

all : $(STATIC)
	@mkdir -p $(OUT_DIR)
	@mv $(STATIC) $(OUT_DIR)
	@echo "Project $(STATIC) is Built"

$(STATIC):$(OBJ)
	@echo "[Link (Static)]"
	@ar rcs $@ $^

.cc.o:
	@echo [Compile] $<
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJ) $(OUT_DIR)

install: all
	@mkdir -p $(DESTDIR)/lib
	@cp -r $(OUT_DIR)/* $(DESTDIR)/lib
#	@install -m 0755 $(OUT_DIR)/* $(DESTDIR)/lib

.PHONY: all install clean lib
