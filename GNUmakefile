EXE = BNL1tonTriggeredCosmics
CXXFLAGS += -I$(CRY_ROOT)/src

default: BNL1tonTriggeredCosmics

BNL1tonTriggeredCosmics: $(CRY_ROOT)/lib/libCRY.a
	$(CXX) $(CXXFLAGS) -I$(ROOTSYS)/include -o $@ $@.cc -L$(CRY_ROOT)/lib -lCRY $(shell root-config --libs)

clean :
	rm -f *.o $(EXE)
