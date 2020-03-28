#include <lv2plugin.hpp>

using namespace LV2;

class Stereodump : public Plugin<Stereodump> {
  public:

    Stereodump(double rate)
      : Plugin<Stereodump>(4) {
      }

    void run(uint32_t nframes) {
      float l = *p(0);
      float r = *p(1);
      printf("%.16f %.16f\n", l, r);
    }

};

static int _ = Stereodump::register_class("http://ll-plugins.nongnu.org/lv2/lv2pftci/stereodump");
