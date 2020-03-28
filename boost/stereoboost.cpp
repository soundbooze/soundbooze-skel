#include <lv2plugin.hpp>

using namespace LV2;

class Stereoboost : public Plugin<Stereoboost> {
  public:

    Stereoboost(double rate)
      : Plugin<Stereoboost>(4) {
      }

    void run(uint32_t nframes) {
      for (uint32_t i = 0; i < nframes; ++i) {
        p(2)[i] = p(0)[i] * 20.9;
        p(3)[i] = p(1)[i] * 20.9;
      }
    }

};

static int _ = Stereoboost::register_class("http://ll-plugins.nongnu.org/lv2/lv2pftci/stereoboost");
