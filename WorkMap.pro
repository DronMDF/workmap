
TEMPLATE = app
CONFIG += qt warn_on debug exceptions rtti valgrind

HEADERS = WMApplication.h WMSettings.h WMWindow.h
SOURCES = WorkMap.cpp WMApplication.cpp WMWindow.cpp
RESOURCES = WMResources.qrc

TARGET = WorkMap
