CXX = clang++
CXXFLAGS = -std=c++11 -Iinclude -I./json/single_include -I/opt/homebrew/include -I/opt/homebrew/Cellar/librdkafka/2.8.0/include/librdkafka -Wall -Wextra
LDFLAGS = -L/opt/homebrew/lib -lrdkafka

SRCDIR = src
BUILDDIR = build
TARGET = $(BUILDDIR)/quant_risk_engine

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR)/*

.PHONY: all clean
