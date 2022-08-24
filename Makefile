# If compiling on Windows, the following lines may need to be changed to fit the system environment.
CC = gcc
CP = cp
MKDIR = mkdir
RM = rm

LIB_NAME = liblcstring.o
SRC_DIR = src
SRC = LCString.c
HEADER = LCString.h
DIST_DIR = dist

$(DIST_DIR)/$(LIB_NAME): $(DIST_DIR) $(SRC_DIR)/$(SRC) 
	$(CC) -c -o $(DIST_DIR)/$(LIB_NAME) $(SRC_DIR)/$(SRC)
	$(CP) $(SRC_DIR)/$(HEADER) $(DIST_DIR)/include/$(HEADER)

.PHONY:doxygen
doxygen: doc $(DIST_DIR)/$(LIB_NAME)
	doxygen -w html doc/header.html doc/footer.html doc/stylesheet.css
	doxygen

$(DIST_DIR):
	$(MKDIR) $(DIST_DIR)
	$(MKDIR) $(DIST_DIR)/include

doc:
	$(MKDIR) doc

.PHONY: clean
clean:
	$(RM) -rf $(DIST_DIR)