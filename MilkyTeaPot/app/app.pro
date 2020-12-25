QT += core gui widgets

TEMPLATE = app

CONFIG += \
          c++11

TARGET = MilkyTeaPot

DESTDIR = bin

SOURCES += \
    src/plugin/plugin_base.cc \
    src/plugin/plugin_manager.cc \
    src/ui/ui_mainwindow.cc \
    src/file_holder.cc \
    src/mainwindow.cc \
    src/main.cc

HEADERS += \
    src/plugin/plugin_base.h \
    src/plugin/plugin_manager.h \
    src/ui/ui_mainwindow.h \
    src/file_holder.h \
    src/mainwindow.h \
    settings.h

HEADERS += extern/base_plugin.h
