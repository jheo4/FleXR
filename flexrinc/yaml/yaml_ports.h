#ifndef __FLEXR_YAML_PORTS__
#define __FLEXR_YAML_PORTS__

#include <bits/stdc++.h>
#include "defs.h"

namespace flexr
{
  namespace yaml
  {
    class YamlInPort
    {
      public:
        std::string portName;
        std::string connectionType;
        int bindingPortNum;

        void print()
        {
          std::cout << "Inport -------- " << std::endl;
          std::cout << "\tPort Name: " << portName << std::endl;
          std::cout << "\tConnection Type: " << connectionType << std::endl;
          if(connectionType == std::string("remote")) {
            std::cout << "\tBinding Port Number: " << bindingPortNum << std::endl;
          }
        }
    };


    class YamlOutPort
    {
      public:
        std::string portName;
        std::string connectionType;
        std::string connectingAddr;
        int connectingPortNum;
        std::string connectingKernelId, connectingPortName;
        std::string duplicatedFrom;

        void print()
        {
          std::cout << "Outport -------- " << std::endl;
          std::cout << "\tPort Name: " << portName << std::endl;
          std::cout << "\tConnection Type: " << connectionType << std::endl;
          if(duplicatedFrom != "")
          {
            std::cout << "\tDuplicated From: " << duplicatedFrom << std::endl;
          }
          if(connectionType == std::string("remote"))
          {
            std::cout << "\tRemote Address: " << connectingAddr << std::endl;
            std::cout << "\tRemote Port Number: " << connectingPortNum << std::endl;
          }
        }
    };
  }
}
#endif
