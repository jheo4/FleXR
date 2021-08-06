#ifndef __FLEXR_COMPONENT_ROSBAG_READER__
#define __FLEXR_COMPONENT_ROSBAG_READER__

#include <rosbag/bag.h>
#include <rosbag/view.h>

#include "defs.h"
#include "types/types.h"

namespace flexr {
  namespace components {

    /**
     * @brief Component to read recorded bag files
     */
    class ROSBagReader {
    protected:
      rosbag::Bag bag;
      rosbag::View *view;
      rosbag::View::iterator curMsg;

    public:
      ROSBagReader();


      /**
       * @brief Initialize bag viewer with the topic subscription
       * @param bagFile
       *  Bag file name to open
       * @param topic
       *  Topic name to subscribe
       */
      ROSBagReader(std::string bagFile, std::string topic);


      /**
       * @brief Open a bag file and set bag viewer with the topic subscription
       * @param bagFile
       *  Bag file name to open
       * @param topic
       *  Topic name to subscribe
       */
      bool openBag(std::string bagFile, std::string topic);


      void clearSession();
      ~ROSBagReader();
    };
  }
}
#endif

