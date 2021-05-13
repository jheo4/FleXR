#ifndef __MXRE_OBJ_CTX_EXTRACTOR__
#define __MXRE_OBJ_CTX_EXTRACTOR__

#include <bits/stdc++.h>
#include <raft>

#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/highgui.hpp>

#include <glm/glm.hpp>
#include "defs.h"
#include "types/cv/types.h"
#include "types/gl/types.h"
#include "types/clock_types.h"
#include "types/frame.h"
#include "kernels/kernel.h"

namespace mxre
{
  namespace kernels
  {
    using CtxExtractorInMarkerType = types::Message<std::vector<cv_types::DetectedMarker>>;
    using CtxExtractorOutCtxType   = types::Message<std::vector<gl_types::ObjectContext>>;

    class MarkerCtxExtractor : public MXREKernel
    {
    private:
      // TODO: components::ORBDetector: detect & ctx extraction
      cv::Mat camIntrinsic;
      cv::Mat camDistCoeffs;
      int width, height;

    public:
      MarkerCtxExtractor(int width=1280, int height=720);
      MarkerCtxExtractor(int width, int height, cv::Mat intrinsic, cv::Mat distCoeffs);
      void setIntrinsic(cv::Mat inIntrinsic) {camIntrinsic = inIntrinsic.clone();}
      void setDistCoeffs(cv::Mat inDistCoeffs) {camDistCoeffs = inDistCoeffs.clone();}
      virtual raft::kstatus run();
      bool logic(CtxExtractorInMarkerType *inDetectedMarkers, CtxExtractorOutCtxType *outMarkerContexts);
    };

  }   // namespace pipeline
} // namespace mxre

#endif

