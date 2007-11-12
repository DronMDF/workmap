
TEMPLATE = app
CONFIG += qt warn_on debug exceptions rtti

HEADERS = WMApplication.h WMSettings.h WMWindow.h WMModel.h WMItem.h
SOURCES = WorkMap.cpp WMApplication.cpp WMWindow.cpp WMModel.cpp WMItem.cpp
RESOURCES = WMResources.qrc

TARGET = WorkMap

include (../Test/modeltest-0.1/modeltest.pri)
