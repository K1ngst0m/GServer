//
// Created by Npchitman on 2021/4/1.
//

#ifndef GSERVER_CMDOPTIONS_H
#define GSERVER_CMDOPTIONS_H

#include <algorithm>
#include <functional>
#include <string>

#define BIND_CMD(argc, argv, fn) [begin = argv, end = argc + argv](auto && option, auto && action) { return fn(begin, end, std::forward<decltype(option)>(option), std::forward<decltype(action)>(action)); };

namespace CmdOption{

        void GetOption(char ** begin, char ** end,
                       const std::string & option,
                       const std::function<void(std::string)>& action)
        {
            char ** itr = std::find(begin, end, option);
            auto parameter = itr != end && ++itr != end ? *itr : nullptr;
            action(parameter);
        }

        void OptionExists(char** begin, char** end,
                          const std::string& option,
                          const std::function<void(bool)>& action)
        {
            auto parameter = std::find(begin, end, option) != end;
            action(parameter);
        }

}


#endif //GSERVER_CMDOPTIONS_H
