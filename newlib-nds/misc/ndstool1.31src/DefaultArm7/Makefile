#just grab the latest arm7 binary we got earlier
all:	grabTGDSARM7


grabTGDSARM7:
	-@wget	-O $(CURDIR)/default_arm7.bin	https://github.com/cotodevel/ToolchainGenericDS-template/raw/master/arm7/prebuilt-armcore/arm7.bin
	-@echo 'DefaultArm7: default_arm7.bin ready'
	
clean:
	-rm -fr default_arm7.bin