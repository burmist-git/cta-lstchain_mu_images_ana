ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)
#
ROOTLIBS += -lMinuit2 -lMinuit

CXX  = g++
CXX += -I./	
CXX += -I./obj/

CXXFLAGS  = -g -Wall -fPIC -Wno-deprecated
CXXFLAGS += $(ROOTCFLAGS)
CXXFLAGS += -Wreorder

OUTLIB = ./obj/

#----------------------------------------------------#

all: makedir runana 

makedir:
	mkdir -p $(OUTLIB);

.PHONY: printmakehelp_and_reminder
printmakehelp_and_reminder: runana.cpp Makefile
	$(info  /*****************************************************************/)
	$(info  * task --> printmakehelp_and_reminder: convert2root.cpp Makefile *)
	$(info  * $$@ ----> $@                            *)
	$(info  * $$< --------------------------------> $<                *)
	$(info  * $$^ --------------------------------> $^   	*)
	$(info  /*****************************************************************/)

runana: runana.cpp src/pixel_info.hh obj/pmtCameraHist.o obj/muonRingFitter.o obj/dbscan.o obj/dl1_muon_csv_reader.o obj/plt.o
	$(CXX) -o runana runana.cpp $(OUTLIB)*.o $(ROOTCFLAGS) $(ROOTLIBS) $(ROOTGLIBS)

obj/muonRingFitter.o: src/muonRingFitter.cpp src/muonRingFitter.hh
	$(CXX) $(CXXFLAGS) -c -I. -o $@ $<

obj/dbscan.o: src/dbscan.cpp src/dbscan.hh
	$(CXX) $(CXXFLAGS) -c -I. -o $@ $<

obj/pmtCameraHist.o: src/pmtCameraHist.cpp src/pmtCameraHist.hh src/pixel_info.hh
	$(CXX) $(CXXFLAGS) -c -I. -o $@ $<

obj/dl1_muon_csv_reader.o: src/dl1_muon_csv_reader.cpp src/dl1_muon_csv_reader.hh
	$(CXX) $(CXXFLAGS) -c -I. -o $@ $<

obj/plt.o: src/plt.cpp src/plt.hh obj/pmtCameraHist.o obj/dl1_muon_csv_reader.o
	$(CXX) $(CXXFLAGS) -c -I. -o $@ $<

clean:
	rm -f runana
	rm -f *~
	rm -f src/*~
	rm -f $(OUTLIB)*.o
