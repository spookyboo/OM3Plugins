QT       += widgets opengl multimedia
OGAMHOME = "../../Ogam"

TARGET = OgamGitResourcePlugin
TEMPLATE = lib

# Used in defining __declspec export/import
DEFINES += OGAM_GITRESOURCE_PLUGIN_LIBRARY

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
    src/ogam_gitresource_plugin.cpp

HEADERS +=\
    header/ogam_gitresource_plugin.h \
    header/git_resource_constants.h

INCLUDEPATH +=\
    "../OgamGitResourcePlugin/header/" \
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

Release:DESTDIR = "$$OGAMHOME/bin"
Debug:DESTDIR = "$$OGAMHOME/bin"
target.path = $$[QTDIR]/
INSTALLS += target
