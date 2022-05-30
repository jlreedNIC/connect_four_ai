# macros
gxx = g++ -std=c++11
flags = -Wall -Wextra -pedantic -pedantic-errors
# sfml = -lsfml-window -lsfml-graphics -lsfml-system

# files
exec = ConnectFourText.exe
# src = sourcefiles
obj = obj

# pattern
$(obj)/%.o : %.cpp
	mkdir -p $(obj)
	$(gxx) $(flags) $< -c -o $@ 

$(exec) : $(obj)/mainText.o $(obj)/environment.o $(obj)/agent.o $(obj)/textApp.o
	$(gxx) $(flags) $^ -o $@ 

$(obj)/mainText.o : textApp.h

$(obj)/textApp.o : agent.h environment.h

$(obj)/agent.o : environment.h

test: $(exec)
	./$(exec)

clean:
	rm -rf $(obj)
	rm $(exec)
