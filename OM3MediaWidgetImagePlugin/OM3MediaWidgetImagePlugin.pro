QT       += widgets opengl multimedia
OM3HOME = "../../OM3"

TARGET = OM3MediaWidgetImagePlugin
TEMPLATE = lib

# Used in defining __declspec export/import
DEFINES += OM3_MEDIAWIDGET_IMAGE_PLUGIN_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES +=\
    src/media_image_widget.cpp \
    src/OM3_media_widget_image_plugin.cpp

HEADERS +=\
    header/media_image_widget.h \
    header/media_widget_image_constants.h \
    header/OM3_media_widget_image_plugin.h

INCLUDEPATH +=\
    "../OM3MediaWidgetImagePlugin/header/" \
    "$$OM3HOME/source/header"

Debug:LIBS += -L"$$OM3HOME/bin"
Debug:LIBS += -L"bin"
Release:LIBS += -L"$$OM3HOME/bin"

CONFIG(debug, debug|release):LIBS +=\
        -lOM3
        -lOM3MediaWidgetImagePlugin

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
