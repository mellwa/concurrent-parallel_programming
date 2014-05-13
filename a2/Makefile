TYPE:=int
OPT:=

CXX = u++					# compiler
CXXFLAGS = -g -multi -Wall -Wno-unused-label -MMD ${OPT} -DTYPE="${TYPE}" # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS1 = q1.o q1driver.o# list of object files for question 1 prefixed with "q1"
EXEC1 = tokenring

OBJECTS3 = q3.o q3driver.o# list of object files for question 3 prefixed with "q3"
EXEC3 = quicksort

OBJECTS = ${OBJECTS1} ${OBJECTS3}		# all object files
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXECS = ${EXEC1} ${EXEC3}			# all executables

#############################################################

.PHONY : all clean

all : ${EXECS}					# build all executables

${EXEC1} : ${OBJECTS1}				# link step 1st executable
	${CXX} ${CXXFLAGS} $^ -o $@

-include ImplType

ifeq (${IMPLTYPE},${TYPE})			# same implementation type as last time ?
${EXEC3} : ${OBJECTS3}
	${CXX} ${CXXFLAGS} $^ -o $@
else
ifeq (${TYPE},)					# no implementation type specified ?
# set type to previous type
TYPE=${IMPLTYPE}
${EXEC3} : ${OBJECTS3}
	${CXX} ${CXXFLAGS} $^ -o $@
else						# implementation type has changed
.PHONY : ${EXEC3}
${EXEC3} :
	rm -f ImplType
	touch q3${EXEC3}.h
	${MAKE} TYPE="${TYPE}"
endif
endif

ImplType :
	echo "IMPLTYPE=${TYPE}" > ImplType
	sleep 1

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXECS} ImplType