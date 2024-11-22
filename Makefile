TARGET= gol
$(TARGET) : $(TARGET).cpp
	g++ -Wall -O2 $$(pkg-config --cflags ncurses) main.cpp $(TARGET).cpp $$(pkg-config --libs ncurses) -o $(TARGET)

.PHONY: clean
clean:
	rm -i $(TARGET)