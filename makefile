# macros
gxx = g++ -std=c++17
flags = -Wall -Wextra -pedantic -pedantic-errors
sfml = -lsfml-window -lsfml-graphics -lsfml-system

# files
exec = ConnectFour.app
src = sourcefiles
obj = $(src)/obj
txt = $(src)/text_based

# pattern
$(obj)/%.o : $(src)/%.cpp
	mkdir -p $(obj)
	$(gxx) $(flags) $< -c -o $@ $(sfml)

$(exec) : $(obj)/main.o $(obj)/app.o  $(obj)/agent.o $(obj)/environment.o
	$(gxx) $(flags) $^ -o $@ $(sfml)

$(obj)/main.o : $(src)/app.h

$(obj)/agent.o: $(src)/environment.h

$(obj)/app.o: $(src)/agent.h $(src)/environment.h

test: $(exec)
	./$(exec)

clean:
	rm -rf $(obj)
	rm $(exec)
