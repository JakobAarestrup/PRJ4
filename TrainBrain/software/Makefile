SOURCES=trainBrain.cpp HandDetector/handDetector.cpp Motor/PID.cpp BossBoundary/bossBoundary.cpp Motor/Motor.cpp Measurement/Measurement.cpp Somo/wiringSerial.c Measurement/softPwm.c Measurement/wiringPi.c
OBJECTS=$(addprefix $(BUILD_DIR), $(SOURCES:.cpp=.o))
DEPS=$(SOURCES:.cpp=.d)
EXE=main
CXXFLAGS=-I. -pthread -lpigpio -lrt -lwiringPi

# Making for host
# > make ARCH=host
ifeq (${ARCH},host)
CXX=g++
BUILD_DIR=build/host/#tilføjet "/" for at indikere filerne skal ligges ind i mappen "host"
EXE_DIR=bin/host/#tilføjet program mappe, for at sepere de 2 .exe filer
endif

# Making for target
# > make ARCH=target
ifeq (${ARCH},target)
CXX=arm-rpizw-g++
BUILD_DIR=build/target/
EXE_DIR=bin/target/
endif

$(EXE_DIR)$(EXE): $(DEPS) $(OBJECTS) # << Check the $(DEPS) new dependency
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

# %.cpp -> %.o needs to be added! Target is NOT just %.o...
$(BUILD_DIR)%.o: %.cpp # tilføjede kode for at lave .cpp filer om til .o
	$(CXX) -c $(CXXFLAGS) -o $@ $<

# Rule that describes how a .d (dependency) file is created from a .cpp file
# Similar to the assigment that you just completed %.cpp -> %.o
%.d: %.cpp
	$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >> $@

format: $(SOURCES:.cpp=.format) # 4.1

%.format: %.cpp
	@echo "Formatting file '$<'"...
	@clang-format -i $<
	@echo "" > $@

tidy: $(SOURCES:.cpp=.tidy) # 4.2

%.tidy: %.cpp
	@echo "Tidying file '$<'"...
	@clang-tidy $< -- $(CXXFLAGS)
	@echo "" > $@

.PHONY: clean #virker kun i GNU

clean: #tilføjede clean for at rydde op i mapperne
	rm $(BUILD_DIR)*.o *.d
ifneq ($(filter-out clean format tidy ,$(MAKECMDGOALS)),) #4.3
	-include $(DEPS)
endif
# ifneq ($(MAKECMDGOALS),clean) # old 3.1
# -include $(DEPS)
# endif
