BUNDLE = lv2pftci-stereoboost.lv2
INSTALL_DIR = /usr/local/lib/lv2


$(BUNDLE): manifest.ttl stereoboost.ttl stereoboost.so
	rm -rf $(BUNDLE)
	mkdir $(BUNDLE)
	cp manifest.ttl stereoboost.ttl stereoboost.so $(BUNDLE)

stereoboost.so: stereoboost.cpp
	g++ -shared -fPIC -DPIC stereoboost.cpp `pkg-config --cflags --libs lv2-plugin` -o stereoboost.so

install: $(BUNDLE)
	mkdir -p $(INSTALL_DIR)
	rm -rf $(INSTALL_DIR)/$(BUNDLE)
	cp -R $(BUNDLE) $(INSTALL_DIR)

clean:
	rm -rf $(BUNDLE) stereoboost.so
