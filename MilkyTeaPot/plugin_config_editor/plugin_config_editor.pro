QT += core gui widgets

TEMPLATE = lib

CONFIG += \
          c++11 \
          plugin

TARGET = config_editor

DESTDIR = plugins/config_editor

SOURCES += \
    src/preference_item.cc \
    src/plugin/plugin_config_editor.cc \
    src/ui/ui_config_text_edit.cc \
    src/ui/ui_preference_editer.cc \
    src/config_text_edit.cc \
    src/preference_editer.cc \
    src/lib.cc

HEADERS += \
    src/preference_item.h \
    src/plugin/plugin_config_editor.h \
    src/ui/ui_config_text_edit.h \
    src/ui/ui_preference_editer.h \
    src/config_text_edit.h \
    src/preference_editer.h \
    settings.h

DEPENDPATH += ../app/src/plugin/plugin_base.h
