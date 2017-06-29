EXE = BNL1tonTriggeredCosmics
CXXFLAGS += -I$(CRYHOME)/src

default: BNL1tonTriggeredCosmics

BNL1tonTriggeredCosmics: $(CRYHOME)/lib/libCRY.a
	$(CXX) $(CXXFLAGS) -I$(ROOTSYS)/include -o $@ $@.cc -L$(CRYHOME)/lib -lCRY $(shell root-config --libs)

clean :
	rm -f *.o $(EXE)
