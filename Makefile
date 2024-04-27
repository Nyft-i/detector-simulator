# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11

# Source files
SRCS = detector_simulation.cpp depositor_particle.cpp particle.cpp photon.cpp electron.cpp nucleon.cpp muon.cpp tau.cpp neutrino.cpp sub_detector.cpp tracker.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = detector_simulation.exe

# Default target
all: $(TARGET)

# Compile source files into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)