#include "plugin_base.h"

#include "plugin_manager.h"

namespace Plugin {

Callbacks::~Callbacks() {
}

Callbacks::Callbacks(QObject *parent)
    : QObject(parent) {
}

} // namespace Plugin
