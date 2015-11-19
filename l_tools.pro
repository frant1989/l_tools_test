#-------------------------------------------------
#
# Project created by QtCreator 2014-04-17T13:09:42
#
#-------------------------------------------------

QT       += xml gui declarative


TARGET = l_tools
TEMPLATE = lib


#path to pro file
HOME_APP = $$PWD

#directory common lib
LIBDIR = $$HOME_APP/../../Build/Lib
OBJ_DIR= $$HOME_APP/../../Build/Obj
MOC = $$HOME_APP/../../Build/Moc

CONFIG += debug_and_release
CONFIG += staticlib c++11
QMAKE_CXXFLAGS += -std=c++11

CXXFLAGS="-std=c++0x"

#path to debug and release Bin,Obj,MOC
CONFIG(debug) {
 OBJECTS_DIR = $$OBJ_DIR/debug/l_tools
 MOC_DIR =  $$MOC/debug/l_tools
 DESTDIR = $${LIBDIR}/debug/
} else {
 OBJECTS_DIR = $$OBJ_DIR/release/l_tools
 MOC_DIR =  $$MOC/release/l_tools
 DESTDIR = $${LIBDIR}/release/
}
#include path to
INCLUDEPATH += $$PWD
SOURCES += \
    r_xml/r_parser.cpp \
    r_logger/r_logger.cpp \
    r_dir/r_dir.cpp \
    r_date/r_date.cpp \
    r_process/r_process.cpp \
    r_thread/r_thread.cpp \
    r_debug/r_debug.cpp \
    r_standard_launch/r_standard_launch.cpp


HEADERS += \
    r_xml/r_parser.h \
    r_logger/r_logger.h \
    r_dir/r_dir.h \
    r_date/r_date.h \
    r_xml/r_parser_net.h \
    r_exceptions/r_exceptions.h \
    r_process/r_process.h \
    r_template/r_template.h \
    r_global/r_global.h \
    r_thread/r_thread.h \
    r_debug/r_debug.h \
    r_standard_launch/r_standard_launch.h

