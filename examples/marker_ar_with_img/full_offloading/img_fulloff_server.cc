#include <raft>
#include <mxre>
#include <bits/stdc++.h>

#define WIDTH 1280
#define HEIGHT 720

using namespace std;


int main(int argc, char const *argv[])
{
  mxre::cv_types::ORBMarkerTracker orbMarkerTracker;
  mxre::cv_utils::setMarkerFromImages("/home/jin/github/mxre/resources/markers/", "720p_marker", 0, 1, orbMarkerTracker);

  raft::map servingPipeline;
  mxre::kernels::ORBDetector orbDetector(orbMarkerTracker.getRegisteredObjects());
  mxre::kernels::MarkerCtxExtractor markerCtxExtractor(WIDTH, HEIGHT);
  mxre::kernels::ObjectRenderer objRenderer(orbMarkerTracker.getRegisteredObjects(), WIDTH, HEIGHT);
  mxre::kernels::FFmpegRTPReceiver rtpReceiver("mjpeg", "localhost", 49985, WIDTH, HEIGHT);
  rtpReceiver.duplicateOutPort<mxre::types::Frame>("out_data", "out_data2");
  mxre::kernels::MessageReceiver<char> keyReceiver(49986, mxre::utils::recvPrimitive<char>);
  mxre::kernels::FFmpegRTPSender rtpSender("mjpeg", "127.0.0.1", 49987, 800000, 10, WIDTH, HEIGHT);

  //mxre::pipeline::output_sinks::CVDisplay cvDisplay;

  servingPipeline += rtpReceiver["out_data"] >> orbDetector["in_frame"];

  servingPipeline += orbDetector["out_detected_markers"] >> markerCtxExtractor["in_detected_markers"];

  servingPipeline += rtpReceiver["out_data2"] >> objRenderer["in_frame"];
  servingPipeline += markerCtxExtractor["out_marker_contexts"] >> objRenderer["in_marker_contexts"];
  servingPipeline += keyReceiver["out_data"] >> objRenderer["in_keystroke"];

  servingPipeline += objRenderer["out_frame"] >> rtpSender["in_data"];

  servingPipeline.exe();
  return 0;
}
