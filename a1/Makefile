CXX = u++					# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD	# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS0 = q1.o			# optional build of given throwcatch program
EXEC0 = throwcatch				# 0th executable name

OBJECTS1 = q1soln.o              # object files forming 1st executable with prefix "q1"
EXEC1 = longjmp					# 1st executable name

OBJECTS00 = q2.o			# optional build of given program
EXEC00 = resumption

OBJECTS2 = q2noresumption.o# object files forming 2st executable with prefix "q2"
EXEC2 = noresumption

OBJECTS3 = q3soln.o# object files forming 3rd executable with prefix "q3"
EXEC3 = floatconstant

OBJECTS = ${OBJECTS1} ${OBJECTS2} ${OBJECTS3}
DEPENDS = ${OBJECTS:.o=.d}
EXECS = ${EXEC1} ${EXEC2} ${EXEC3}

#############################################################

.PHONY : all clean

all : ${EXECS}					# build all executables

q1soln.o : q1soln.cc					# change compiler 1st executable, ADJUST SUFFIX (.cc)
	g++ ${CXXFLAGS} -c $< -o $@

${EXEC0} : ${OBJECTS0}
	g++ ${CXXFLAGS} $^ -o $@

${EXEC1} : ${OBJECTS1}
	g++ ${CXXFLAGS} $^ -o $@

${OBJECTS00} : q2resumption.cc
	u++ ${CXXFLAGS} -c $< -o $@

${EXEC00} : ${OBJECTS00}
	u++ ${CXXFLAGS} $^ -o $@

q2noresumption.o : q2noresumption.cc	       # change compiler 2nd executable, ADJUST SUFFIX (.cc)
	g++ ${CXXFLAGS} -c $< -o $@

${EXEC2} : ${OBJECTS2}
	g++ ${CXXFLAGS} $^ -o $@

${EXEC3} : ${OBJECTS3}
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC0} ${EXEC00} ${EXECS}
