EXE = BNL1tonTriggeredCosmics
CXXFLAGS += -I$(CRYHOME)/src

default: BNL1tonTriggeredCosmics data

BNL1tonTriggeredCosmics: $(CRYHOME)/lib/libCRY.a
	$(CXX) $(CXXFLAGS) -I$(ROOTSYS)/include -o $@ $@.cc -L$(CRYHOME)/lib -lCRY $(shell root-config --libs)

data: $(CRYHOME)/data
	ln -s $(CRYHOME)/data $@

clean :
	rm -f *.o $(EXE)
