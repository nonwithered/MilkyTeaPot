QT += core gui widgets

TEMPLATE = app

CONFIG += \
          c++11

TARGET = MilkyTeaPot

DESTDIR = bin

SOURCES += \
    src/plugin/plugin_base.cc \
    src/plugin/plugin_manager.cc \
    src/ui/ui_main_window.cc \
    src/ui/ui_preferences_dialog.cc \
    src/preferences_dialog.cc \
    src/config_manager.cc \
    src/main_window.cc \
    src/main.cc

HEADERS += \
    src/plugin/plugin_base.h \
    src/plugin/plugin_manager.h \
    src/ui/ui_main_window.h \
    src/ui/ui_preferences_dialog.h \
    src/preferences_dialog.h \
    src/config_manager.h \
    src/main_window.h \
    settings.h
