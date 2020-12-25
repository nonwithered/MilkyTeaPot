QT += core gui widgets

TEMPLATE = lib

CONFIG += \
          c++11 \
          plugin

TARGET = file_editor

DESTDIR = plugins/file_editor

SOURCES += \
    src/plugin/file_editor.cc \
    src/lib.cc

HEADERS += \
    src/plugin/file_editer.h \
    settings.h

INCLUDEPATH += ../app/extern

DEPENDPATH += $$INCLUDEPATH
