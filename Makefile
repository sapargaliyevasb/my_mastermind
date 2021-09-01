CC_OPT=-Wall -Wextra -Werror
PROJ="my_mastermind"
 
all:
  gcc ${CC_OPT} my_mastermind.c -o ${PROJ}
