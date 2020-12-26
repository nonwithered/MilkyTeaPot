#include "plugin_base.h"

#include "plugin_manager.h"

namespace Plugin {

Callbacks::Callbacks(QObject *parent)
    : QObject(parent) {
}

Callbacks::~Callbacks() {
}

} // namespace Plugin
