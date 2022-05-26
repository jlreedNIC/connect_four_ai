# macros
gxx = g++ -std=c++17
flags = -Wall -Wextra -pedantic -pedantic-errors
sfml = -lsfml-window -lsfml-graphics -lsfml-system

# files
exec = ConnectFour.app
src = sourcefiles
obj = $(src)/obj

# pattern
$(obj)/%.o : $(src)/%.cpp
	mkdir -p $(obj)
	$(gxx) $(flags) $^ -c -o $@ $(sfml)

$(exec) : $(obj)/main.o $(obj)/app.o 
	$(gxx) $(flags) $^ -o $@ $(sfml)

test: $(exec)
	./$(exec)

clean:
	rm -rf $(obj)
	rm $(exec)
