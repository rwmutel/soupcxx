#ifndef PROJECT_SOUP_H
#define PROJECT_SOUP_H
#include <memory>
#include <string_view>
#include <filesystem>
#include <vector>
#include <regex>
#include "Node.h"
#include "utils.h"
#include "Tag.h"

class Soup {
public:
    virtual std::string serialize()=0;
};

#endif //PROJECT_SOUP_H
