#include <lv2plugin.hpp>

using namespace LV2;

class Stereoboost : public Plugin<Stereoboost> {
  public:

    Stereoboost(double rate)
      : Plugin<Stereoboost>(5) {
      }

    void run(uint32_t nframes) {

      float boost = *p(0);

      boost = boost < 1 ? 1 : boost;
      boost = boost > 20 ? 20 : boost;

      for (uint32_t i = 0; i < nframes; ++i) {
        p(3)[i] = p(1)[i] * boost;
        p(4)[i] = p(2)[i] * boost;
      }

    }

};

static int _ = Stereoboost::register_class("http://ll-plugins.nongnu.org/lv2/lv2pftci/stereoboost");
