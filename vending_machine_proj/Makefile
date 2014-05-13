CXX = u++					# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD 
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = parent.o vending_machine.o watcard.o watcard_office.o printer.o student.o bank.o name_server.o bottling_plant.o driver.o truck.o config.o
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXEC = soda

.PHONY : clean

all : ${EXEC}					# build all executables

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@


${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC} 
