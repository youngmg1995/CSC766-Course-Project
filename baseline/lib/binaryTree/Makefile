################################################################################
############################# GENERAL DIRECTORIES ##############################
################################################################################
# globals binary /bin
APP                 = run-binaryTree

# dirs Root app
APP_DIR             = .

# dir root/managed_folders
SRC_DIR           	= src
INC_DIR			  	= include
OBJ_DIR				= obj
BIN_DIR			  	= bin



################################################################################
############################ COMPILATION PARAMETERS ############################
################################################################################
# compliler
CC		    = gcc
APP_INC     = -I$(APP_DIR)/$(INC_DIR)

# flags
# CFLAGS   =  -O3 -Wall -m64 -fopenmp -g
CFLAGS   =  -O1 -Wall
LFLAGS 	 = -lm 



################################################################################
############################ COMPILATION VARIABLES #############################
################################################################################
SRC_FILE				= $(wildcard $(APP_DIR)/$(SRC_DIR)/*.c)
OBJ_FILES				= $(patsubst $(APP_DIR)/$(SRC_DIR)/%.c,$(APP_DIR)/$(OBJ_DIR)/%.o,$(SRC_FILE))
INC_FILES				= $(wildcard $(APP_DIR)/$(INC_DIR)/*.h)
ALL_HEADER_FILES		= $(INC_FILES_ALGO)



################################################################################
############################# COMPILATION VARIABLES ############################
################################################################################

.PHONY: all
all: binaryTree

.PHONY: directories
directories :
	@mkdir -p $(APP_DIR)/$(BIN_DIR)
	@mkdir -p $(APP_DIR)/$(OBJ_DIR)


.PHONY: binaryTree
binaryTree : directories $(APP_DIR)/$(BIN_DIR)/$(APP)
	@echo " ****************************************************************************** "
	@echo " * DONE!! NOTHING ELSE TO COMPILE ---> binaryTree: ./$(word 2,$^)"
	@echo " ****************************************************************************** "


$(APP_DIR)/$(BIN_DIR)/$(APP) :  $(OBJ_FILES)
	@$(CC) $(CFLAGS) -o $@ $^  $(LFLAGS)

$(APP_DIR)/$(OBJ_DIR)/%.o : $(APP_DIR)/$(SRC_DIR)/%.c $(INC_FILES)
	@$(CC) $(CFLAGS) $(APP_INC) -c -o $@ $<



################################################################################
############################### Top Level Rules ################################
################################################################################

.PHONY: run
run: run-binaryTree

.PHONY: clean
clean: clean-all

.PHONY: clean-all
clean-all:
	@rm -fr $(APP_DIR)/$(OBJ_DIR)
	@rm -fr $(APP_DIR)/$(BIN_DIR)

.PHONY: run-binaryTree
run-binaryTree: binaryTree
	./$(APP_DIR)/$(BIN_DIR)/$(APP)
#	./$(APP_DIR)/$(BIN_DIR)/$(APP) -f $(FILE_BIN) $(ARGS)
