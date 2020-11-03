#ifndef __MXRE_ILLIXR_SINK__
#define __MXRE_ILLIXR_SINK__

#include <bits/stdc++.h>
#include <zmq.h>
#include "types/cv/types.h"

namespace mxre {
  namespace types {

    template<typename OUT_T>
    class ILLIXRSink {
    private:
      void *ctx;
      void *sock;
      int dtype;

    public:
      ILLIXRSink() {
        ctx = NULL;
        sock = NULL;
      }


      ~ILLIXRSink() {
        if(sock) zmq_close(sock);
        if(ctx) zmq_ctx_destroy(ctx);
      }


      void setup(std::string id, int dtype=MX_DTYPE_PRIMITIVE) {
        this->dtype = dtype;
        ctx = zmq_ctx_new();
        sock = zmq_socket(ctx, ZMQ_REP);
        std::string bindingAddr = "ipc:///tmp/" + id;
        zmq_bind(sock, bindingAddr.c_str());
      }


      void recvPrimitive(OUT_T *data) {
        zmq_recv(sock, data, sizeof(OUT_T), 0);
        debug_print("%d \n", *data);
      }


      void recvCVMat(void *data) {
        cv::Mat *matData = (cv::Mat*)data;
        uint matInfo[MX_MAT_ATTR_NUM];
        void *recvData;

        zmq_recv(sock, matInfo, sizeof(matInfo), 0);
        recvData = new uchar[matInfo[MX_MAT_SIZE_IDX]];

        zmq_recv(sock, recvData, matInfo[MX_MAT_SIZE_IDX], 0);
        mxre::cv_types::Mat temp = mxre::cv_types::Mat(matInfo[MX_MAT_ROWS_IDX], matInfo[MX_MAT_COLS_IDX],
                                                       matInfo[MX_MAT_TYPE_IDX], recvData);
        *matData = temp.cvMat.clone();
      }


      int recv(OUT_T *data) {
        if(sock == NULL) {
          std::cerr << "ILLIXRSink is not set." << std::endl;
          return -1;
        }

        switch(dtype) {
          case MX_DTYPE_PRIMITIVE:
            recvPrimitive(data);
            break;
          case MX_DTYPE_CVMAT:
            recvCVMat(data);
            break;
        }
        zmq_send(sock, "ack", 3, 0);
        return 1;
      }
    };

  }
}

#endif

