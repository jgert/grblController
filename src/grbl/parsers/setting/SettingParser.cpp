//
// Created by Jakub Gert on 10/06/2020.
//

#include <regex>
#include "SettingParser.h"

bool SettingParser::parse(const string &message) {

    static regex r("^\\$([0-9]+)=(.*)$");

    std::smatch cm;

    if (!regex_match(message, cm, r)) {
        return false;
    }

    configItem.code = stoi(cm[1]);
    configItem.value = cm[2];

    return true;
}

const SettingItem &SettingParser::getConfigurationItem() const {
    return configItem;
}
