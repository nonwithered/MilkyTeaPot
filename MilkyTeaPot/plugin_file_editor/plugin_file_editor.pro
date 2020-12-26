QT += core gui widgets

TEMPLATE = lib

CONFIG += \
          c++11 \
          plugin

TARGET = file_editor

DESTDIR = plugins/file_editor

SOURCES += \
    src/text_file_editor.cc \
    src/text_file_manager.cc \
    src/plugin/plugin_file_editor.cc \
    src/ui/ui_text_file_editor.cc \
    src/lib.cc

HEADERS += \
    src/text_file_editor.h \
    src/text_file_manager.h \
    src/plugin/plugin_file_editor.h \
    src/ui/ui_text_file_editor.h \
    settings.h

DEPENDPATH += ../app/src/plugin/plugin_base.h
