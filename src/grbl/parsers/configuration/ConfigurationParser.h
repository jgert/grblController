//
// Created by Jakub Gert on 10/06/2020.
//

#ifndef GRBL_CONFIGURATIONPARSER_H
#define GRBL_CONFIGURATIONPARSER_H

#include <string>

using namespace std;

struct ConfigurationItem {
    unsigned int code;
    string value;
};

class ConfigurationParser {
private:
    ConfigurationItem configItem;
public:
    bool parse(const string &message);
    const ConfigurationItem &getConfigurationItem() const ;
};


#endif //GRBL_CONFIGURATIONPARSER_H
