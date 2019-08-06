.PHONY: mingw linux null

null :
	@echo "make <mingw|linux|clean>"

mingw :
	cd lovely && $(MAKE) opt=mingw
	cp lovely/libLovelyGUI.dll demo/libLovelyGUI.dll
	cd demo && $(MAKE) opt=mingw

linux :
	cd lovely && $(MAKE) opt=linux
	cp lovely/libLovelyGUI.so demo/libLovelyGUI.so
	cd demo && $(MAKE) opt=linux

clean :
	cd lovely && $(MAKE) clean
	cd demo && $(MAKE) clean
