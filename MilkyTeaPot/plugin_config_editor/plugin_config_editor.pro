QT += core gui widgets

TEMPLATE = lib

CONFIG += \
          c++11 \
          plugin

TARGET = config_editor

DESTDIR = plugins/config_editor

SOURCES += \
    src/config_text_edit.cc \
    src/preference_item.cc \
    src/plugin/plugin_config_editor.cc \
    src/ui/ui_config_text_edit.cc \
    src/lib.cc

HEADERS += \
    src/config_text_edit.h \
    src/preference_item.h \
    src/plugin/plugin_config_editor.h \
    src/ui/ui_config_text_edit.h \
    settings.h

DEPENDPATH += ../app/src/plugin/plugin_base.h
