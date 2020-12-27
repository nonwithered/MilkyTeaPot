#ifndef PLUGIN_CONFIG_EDITOR_SETTINGS_H
#define PLUGIN_CONFIG_EDITOR_SETTINGS_H

#define kPluginName "ConfigEditor"

#define kTipCheckShowEditor "show or hide the config editor view"

#define kApplyModify kPluginName ": apply"
#define kTipApplyModify "apply changes of config file"
#define kMsgApplyFailed "Please review your modification"

#define kSettingsFileSuffix ".json"
#define kSettingsFileName "settings" kSettingsFileSuffix

constexpr int kDefaultWidth = 256;
constexpr int kDefaultHeight = 512;

#endif // ifndef PLUGIN_CONFIG_EDITOR_SETTINGS_H
