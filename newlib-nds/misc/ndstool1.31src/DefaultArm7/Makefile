#just grab the latest arm7 binary we got earlier
all:	grabTGDSARM7


grabTGDSARM7:
	-@wget	-O $(CURDIR)/default_arm7.bin	--no-check-certificate	https://bitbucket.org/Coto88/toolchaingenericds-template/raw/60233f76c94b9a8cf68d9e467ae66b4d9e1a4211/arm7/prebuilt-armcore/arm7.bin
	-@echo 'DefaultArm7: default_arm7.bin ready'
	
clean:
	-rm -fr default_arm7.bin