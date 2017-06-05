QT       += widgets opengl multimedia
OM3HOME = "../../OM3"

TARGET = OM3ResourceProviderGitPlugin
TEMPLATE = lib

# Used in defining __declspec export/import
DEFINES += OM3_RESOURCE_PROVIDER_GIT_PLUGIN_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Add media_listwidget.cpp of OM3 project to prevent linking errors
SOURCES += \
    src/OM3_resource_provider_git_plugin.cpp

HEADERS +=\
    header/resource_provider_gitconstants.h \
    header/OM3_resource_provider_git_plugin.h

INCLUDEPATH +=\
    "../OM3ResourceProviderGitPlugin/header/" \
    "$$OM3HOME/source/header"

Debug:LIBS += -L"$$OM3HOME/bin"
Release:LIBS += -L"$$OM3HOME/bin"

CONFIG(debug, debug|release):LIBS +=\
        -lOM3

CONFIG(release, debug|release):LIBS +=\
        -lOM3

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}

Release:DESTDIR = "$$OM3HOME/bin"
Debug:DESTDIR = "$$OM3HOME/bin"
target.path = $$[QTDIR]/
INSTALLS += target
