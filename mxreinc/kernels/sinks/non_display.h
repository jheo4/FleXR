#ifndef __MXRE_NON_DISPLAY__
#define __MXRE_NON_DISPLAY__

#include <bits/stdc++.h>
#include <raft>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/highgui.hpp>
#include "kernels/kernel.h"
#include "defs.h"
#include "types/clock_types.h"
#include "types/frame.h"

namespace mxre
{
  namespace kernels
  {

    class NonDisplay : public MXREKernel
    {
    public:
      NonDisplay();
      virtual raft::kstatus run() override;
    };

  }   // namespace kernels
} // namespace mxre

#endif

