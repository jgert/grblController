//
// Created by Jakub Gert on 10/06/2020.
//

#ifndef GRBL_SETTINGPARSER_H
#define GRBL_SETTINGPARSER_H

#include <string>

using namespace std;

struct SettingItem {
    unsigned int code;
    string value;
};

class SettingParser {
private:
    SettingItem configItem;
public:
    bool parse(const string &message);
    const SettingItem &getConfigurationItem() const ;
};


#endif //GRBL_SETTINGPARSER_H
