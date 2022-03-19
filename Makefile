################################################################################
##                                   FLAGS                                    ##
################################################################################

CXXFLAGS := -std=c++20 -Wall -Wextra -Werror -O2
LDFLAGS  :=

################################################################################
##                                  COMMANDS                                  ##
################################################################################

CXX   := g++
MKDIR := mkdir -p
RM    := rm -f
RMDIR := rm -rf

################################################################################
##                                DIRECTORIES                                 ##
################################################################################

SRCDIR := src
INCDIR := include
OBJDIR := obj
BINDIR := bin
DEPDIR := dep

BIN := $(BINDIR)/main
SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
INC := $(wildcard $(INCDIR)/*.hpp)
DEP := $(wildcard $(DEPDIR)/*.d)

CXXLIBS := $(patsubst %,-I %,$(INCDIR))

################################################################################
##                                   COLORS                                   ##
################################################################################

ifndef NO_COLORS
DEF     := \033[0;38m
RED     := \033[1;31m
GREEN   := \033[1;32m
YELLOW  := \033[1;33m
BLUE    := \033[1;34m
PURPLE  := \033[1;35m
CYAN    := \033[1;36m
WHITE   := \033[1;37m
RES     := \033[0m
endif

define msg-red
printf "${RED}%b${RES}\n" $1
endef

define msg-green
printf "${GREEN}%b${RES}\n" $1
endef

define msg-yellow
printf "${YELLOW}%b${RES}\n" $1
endef

define msg-blue
printf "${BLUE}%b${RES}\n" $1
endef

define msg-purple
printf "${PURPLE}%b${RES}\n" $1
endef

define msg-cyan
printf "${CYAN}%b${RES}\n" $1
endef

################################################################################
##                                 COMPILATION                                ##
################################################################################

.PHONY:
all: $(BIN)

$(BIN): $(OBJ) | $(BINDIR)
	@$(call msg-green,"Gerando executável $@")
	@$(CXX) ${LDFLAGS} $^ -o $@

# Imports auto-generated dependencies
-include $(DEP)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR) $(DEPDIR)
	@$(call msg-cyan,"Compilando artefato $@")
	@$(CXX) -c ${CXXFLAGS} ${CXXLIBS} -MP -MMD -MF $(DEPDIR)/$*.d $< -o $@

.PHONY:
compiledb:
	@$(call msg-blue,"Gerando base de compilação")
	@compiledb -n make

################################################################################
##                                 DIRECTORIES                                ##
################################################################################

$(BINDIR) $(OBJDIR) $(DEPDIR):
	@$(call msg-blue,"Criando diretório $@")
	@$(MKDIR) $@

################################################################################
##                                  CLEANING                                  ##
################################################################################

define rmdir
$(call msg-purple,"Removendo diretório $(strip $1)") && $(RMDIR) $(strip $1)
endef

define rm
$(call msg-purple,"Removendo arquivo $(strip $1)") && $(RM) $(strip $1)
endef

.PHONY:
clean:
	@$(call rmdir,$(OBJDIR))
	@$(call rmdir,$(BINDIR))

.PHONY:
distclean: clean
	@$(call rmdir,$(DEPDIR))
	@$(call rm,compile_commands.json)
