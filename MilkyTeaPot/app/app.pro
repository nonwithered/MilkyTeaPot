QT += core gui widgets

TEMPLATE = app

CONFIG += \
          c++11

TARGET = MilkyTeaPot

DESTDIR = bin

SOURCES += \
    src/config_manager.cc \
    src/plugin/plugin_base.cc \
    src/plugin/plugin_manager.cc \
    src/ui/ui_main_window.cc \
    src/ui/ui_preferences_dialog.cc \
    src/main_window.cc \
    src/preferences_dialog.cc \
    src/main.cc

HEADERS += \
    src/config_manager.h \
    src/plugin/plugin_base.h \
    src/plugin/plugin_manager.h \
    src/ui/ui_main_window.h \
    src/ui/ui_preferences_dialog.h \
    src/main_window.h \
    src/preferences_dialog.h \
    settings.h
