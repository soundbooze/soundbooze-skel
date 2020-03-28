BUNDLE = lv2pftci-stereodump.lv2
INSTALL_DIR = /usr/local/lib/lv2


$(BUNDLE): manifest.ttl stereodump.ttl stereodump.so
	rm -rf $(BUNDLE)
	mkdir $(BUNDLE)
	cp manifest.ttl stereodump.ttl stereodump.so $(BUNDLE)

stereodump.so: stereodump.cpp
	g++ -shared -fPIC -DPIC stereodump.cpp `pkg-config --cflags --libs lv2-plugin` -o stereodump.so

install: $(BUNDLE)
	mkdir -p $(INSTALL_DIR)
	rm -rf $(INSTALL_DIR)/$(BUNDLE)
	cp -R $(BUNDLE) $(INSTALL_DIR)

clean:
	rm -rf $(BUNDLE) stereodump.so
