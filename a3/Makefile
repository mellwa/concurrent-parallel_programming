KIND:=NOBUSY
OPT:=
TYPE:=SEM

CXX = u++					# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD ${OPT} -D"${KIND}" -D"IMPLTYPE_${TYPE}"
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS1 = q1boundedBuffer.o q1producer.o q1consumer.o q1driver.o
EXEC1 = buffer

OBJECTS2 =  q2tallyVotes${TYPE}.o  q2printer.o q2voter.o q2driver.o # list of object files for question 2 prefixed with "q2"
EXEC2 = vote

OBJECTS = ${OBJECTS1} ${OBJECTS2}		# all object files
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXECS = ${EXEC1} ${EXEC2}			# all executables

.PHONY : all clean

all : ${EXECS}					# build all executables

#############################################################

-include ImplKind

ifeq (${IMPLKIND},${KIND})			# same implementation type as last time ?
${EXEC1} : ${OBJECTS1}
	${CXX} ${CXXFLAGS} $^ -o $@
else
ifeq (${KIND},)					# no implementation type specified ?
# set type to previous type
KIND=${IMPLKIND}
${EXEC1} : ${OBJECTS1}
	${CXX} ${CXXFLAGS} $^ -o $@
else						# implementation type has changed
.PHONY : ${EXEC1}

${EXEC1} :
	rm -f ImplKind
	touch q1boundedBuffer.h
	${MAKE} ${EXEC1} KIND=${KIND}
endif
endif

ImplKind :
	echo "IMPLKIND=${KIND}" > ImplKind
	sleep 1

#############################################################

-include ImplType

ifeq (${IMPLTYPE},${TYPE})			# same implementation type as last time ?
${EXEC2} : ${OBJECTS2}
	${CXX} ${CXXFLAGS} $^ -o $@
else
ifeq (${TYPE},)					# no implementation type specified ?
# set type to previous type
TYPE=${IMPLTYPE}
${EXEC2} : ${OBJECTS2}
	${CXX} ${CXXFLAGS} $^ -o $@
else						# implementation type has changed
.PHONY : ${EXEC2}
${EXEC2} :
	rm -f ImplType
	touch q2tallyVotes.h
	${MAKE} ${EXEC2} TYPE="${TYPE}"
endif
endif

ImplType :
	echo "IMPLTYPE=${TYPE}" > ImplType
	sleep 1

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXECS} ImplKind ImplType
