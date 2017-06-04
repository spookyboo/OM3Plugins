#-------------------------------------------------
#
# Project created by QtCreator 2017-05-25T20:54:30
#
#-------------------------------------------------

QT       += widgets opengl multimedia
OGAMHOME = "../../Ogam"

TARGET = OgamFileResourcePlugin
TEMPLATE = lib

# Used in defining __declspec export/import
DEFINES += OGAM_FILERESOURCE_PLUGIN_LIBRARY

# Used to determine wether resourcs in subdirectories are included when a toplevel directory is selected.
# Note, that in that case no directory tree is shown; all resources are associated with the toplevel directory
# If PLUGIN_INCLUDE_SUBDIRS is defined, subdirs are included, otherwise only the resources that are part of the
# toplevel directory are included
DEFINES += PLUGIN_INCLUDE_SUBDIRS

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


# Add media_listwidget.cpp of Ogam project to prevent linking errors
SOURCES +=\
    src/ogam_fileresource_plugin.cpp \
    src/central_dockwidget.cpp \
    src/file_explorer_dockwidget.cpp \
    "$$OGAMHOME/source/src/media_listwidget.cpp"

HEADERS +=\
    header/ogam_fileresource_plugin.h \
    header/central_dockwidget.h \
    header/file_explorer_dockwidget.h \
    header/file_resource_constants.h

INCLUDEPATH +=\
    "../OgamFileResourcePlugin/header/" \
    "$$OGAMHOME/source/header"

Debug:LIBS += -L"$$OGAMHOME/bin"
Release:LIBS += -L"$$OGAMHOME/bin"

CONFIG(debug, debug|release):LIBS +=\
        -lOgam

CONFIG(release, debug|release):LIBS +=\
        -lOgam

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}

#Release:DESTDIR = ../OgamFileResourcePlugin/bin
#Debug:DESTDIR = ../OgamFileResourcePlugin/bin
Release:DESTDIR = "$$OGAMHOME/bin"
Debug:DESTDIR = "$$OGAMHOME/bin"
target.path = $$[QTDIR]/
INSTALLS += target
