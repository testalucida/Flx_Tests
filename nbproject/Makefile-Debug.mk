#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/2a7bc4b/CalendarController.o \
	${OBJECTDIR}/_ext/2a7bc4b/DayTable.o \
	${OBJECTDIR}/_ext/2a7bc4b/DayTableModel.o \
	${OBJECTDIR}/_ext/2a7bc4b/Flx_Calendar.o \
	${OBJECTDIR}/_ext/2a7bc4b/SimpleTable.o \
	${OBJECTDIR}/src/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=`fltk-config --cxxflags` 
CXXFLAGS=`fltk-config --cxxflags` 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../My_1_5/lib/Debug -L../../fltk-1.3.3/lib -L/usr/local/lib -L/usr/lib -lmy_1_5 -lfltk_forms -lfltk_images -lfltk_jpeg -lfltk_png

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flx_tests

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flx_tests: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flx_tests ${OBJECTFILES} ${LDLIBSOPTIONS} `fltk-config --use-images --ldstaticflags` `mysql_config --libs`

${OBJECTDIR}/_ext/2a7bc4b/CalendarController.o: /home/max/cpp/fltk/Flx_Tests/src/Flx_Calendar/CalendarController.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2a7bc4b
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.3 -I../../My_1_5 -I. -I/home/max/cpp/fltk/Flx_Tests/src -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2a7bc4b/CalendarController.o /home/max/cpp/fltk/Flx_Tests/src/Flx_Calendar/CalendarController.cpp

${OBJECTDIR}/_ext/2a7bc4b/DayTable.o: /home/max/cpp/fltk/Flx_Tests/src/Flx_Calendar/DayTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2a7bc4b
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.3 -I../../My_1_5 -I. -I/home/max/cpp/fltk/Flx_Tests/src -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2a7bc4b/DayTable.o /home/max/cpp/fltk/Flx_Tests/src/Flx_Calendar/DayTable.cpp

${OBJECTDIR}/_ext/2a7bc4b/DayTableModel.o: /home/max/cpp/fltk/Flx_Tests/src/Flx_Calendar/DayTableModel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2a7bc4b
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.3 -I../../My_1_5 -I. -I/home/max/cpp/fltk/Flx_Tests/src -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2a7bc4b/DayTableModel.o /home/max/cpp/fltk/Flx_Tests/src/Flx_Calendar/DayTableModel.cpp

${OBJECTDIR}/_ext/2a7bc4b/Flx_Calendar.o: /home/max/cpp/fltk/Flx_Tests/src/Flx_Calendar/Flx_Calendar.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2a7bc4b
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.3 -I../../My_1_5 -I. -I/home/max/cpp/fltk/Flx_Tests/src -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2a7bc4b/Flx_Calendar.o /home/max/cpp/fltk/Flx_Tests/src/Flx_Calendar/Flx_Calendar.cpp

${OBJECTDIR}/_ext/2a7bc4b/SimpleTable.o: /home/max/cpp/fltk/Flx_Tests/src/Flx_Calendar/SimpleTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2a7bc4b
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.3 -I../../My_1_5 -I. -I/home/max/cpp/fltk/Flx_Tests/src -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2a7bc4b/SimpleTable.o /home/max/cpp/fltk/Flx_Tests/src/Flx_Calendar/SimpleTable.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.3 -I../../My_1_5 -I. -I/home/max/cpp/fltk/Flx_Tests/src -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flx_tests

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
