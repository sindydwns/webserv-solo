SERVER = server
CLIENT = client
.DEFAULT_GOAL = all

CXXFLAGS = -std=c++98 -Wall -Wextra -Werror -MMD -MP -g3
SERVERSRC = \
	parser/Parser.cpp \
	parser/ParseResult.cpp \
	parser/APattern.cpp \
	parser/PatternOptionGroup.cpp \
	parser/PatternSequenceGroup.cpp \
	parser/PatternEqual.cpp \
	parser/PatternReadUntil.cpp \
	parser/PatternWord.cpp \
	parser/PatternReadAll.cpp \
	parser/PatternSkipWs.cpp \
	parser/ParseStream.cpp \
	delegator/Delegator.cpp \
	delegator/ServerDelegator.cpp \
	delegator/ClientDelegator.cpp \
	Config.cpp \
	$(SERVER).cpp
CLIENTSRC = \
	$(CLIENT).cpp
.PHONY: all clean fclean re test

all: $(SERVER) $(CLIENT)

DEP = $(SERVERSRC:.cpp=.d)
-include $(DEP)

$(SERVER): $(SERVERSRC:.cpp=.o)
	$(CXX) $(CXXFLAGS) $(OUTPUT_OPTION) $(SERVERSRC:.cpp=.o)

$(CLIENT): $(CLIENTSRC:.cpp=.o)
	$(CXX) $(CXXFLAGS) $(OUTPUT_OPTION) $(CLIENTSRC:.cpp=.o)

$(CLASS:.cpp=.o): %.o: %.cpp %.hpp

clean:
	find . -type f \( -name '*.o' -or -name '*.d' \) -print -delete

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean
	make all

test: all
	./$(SERVER) | (sleep 1 && ./$(CLIENT))
