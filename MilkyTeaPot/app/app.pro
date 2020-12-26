QT += core gui widgets

TEMPLATE = app

CONFIG += \
          c++11

TARGET = MilkyTeaPot

DESTDIR = bin

SOURCES += \
    src/plugin/plugin_base.cc \
    src/plugin/plugin_manager.cc \
    src/preferences_dialog.cc \
    src/ui/ui_main_window.cc \
    src/ui/ui_preferences_dialog.cc \
    src/main_window.cc \
    src/file_holder.cc \
    src/main.cc

HEADERS += \
    src/plugin/plugin_base.h \
    src/plugin/plugin_manager.h \
    src/ui/ui_main_window.h \
    src/ui/ui_preferences_dialog.h \
    src/preferences_dialog.h \
    src/main_window.h \
    src/file_holder.h \
    settings.h

HEADERS += \
    extern/plugin_interface.h
