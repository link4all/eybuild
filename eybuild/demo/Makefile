
SRC 	= prj/demo.c \
		  cspsrc/demo_csp_maplist.c \
	 	  cspsrc/demo_rom_maplist.c


TARGET	= demo.cgi
CFLAGS	= -g -I$(EYBUILD_BASE)/include 
LIBS	= $(EYBUILD_BASE)/lib/eybuildlib 

$(TARGET): $(SRC)
	gcc $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

all:
	-./demo.unix
	gcc $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)


clean:
	@echo clean target files...
	@if [ -f demo.cgi ];	then \
		rm demo.cgi; \
	fi

