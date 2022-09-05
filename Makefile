CFLAGS =			-Wall -Wextra -Werror

HDRS =				minirt.h

HDRS_DIR =			./includes/

CC =				cc

#BONUSDIR =			bonus/

#BONUS =				$(addprefix ${BONUSDIR}, minirt)

RM =				rm -rf

NAME =				minirt

SRC =				main.c

SRC_DIR =			./src/

HEADERS =			$(addprefix ${HDRS_DIR}, ${HDRS})

SOURCES =			$(addprefix ${SRC_DIR}, ${SRC})

BUILDIR = 			./obj/

BUILDIRS =			echo/ cd/ env/ pwd/ utils/ pipex/ exec/ parser/ export/ exit/ libft/

BLDRS =				$(addprefix ${BUILDIR}, ${BUILDIRS})

OBJS =				$(addprefix ${BUILDIR}, ${SRC:.c=.o})

LIBFT_NAME =		libft.a

LIBFTDIR =			./libft/

LIBFT =				$(addprefix ${LIBFTDIR}, ${LIBFT_NAME})

MLX_NAME =			libmlx.a

MLXDIR =			./mlx/

MLX =				$(addprefix ${MLX_NAME}, ${MLX_NAME})

INCLUDE = 			-I./mlx -I./includes -I./libft

LIBS = 				-L./mlx/ -lmlx -lm -L./libft/ -lft -framework OpenGL -framework AppKit

.PHONY:				clean all fclean re

all:				${BUILDIR} ${BLDRS} ${LIBFT} ${MLX} ${NAME}

${LIBFT}:
					${MAKE} -C ${LIBFTDIR}

${MLX}:
					${MAKE} -C ${MLXDIR}

${NAME}:			${HEADERS}
					${CC} ${INCLUDE} ${CFLAGS} ${SOURCES} ${LIBS} -o $@

${BUILDIR}:
					mkdir -p $@

${BLDRS}:
					mkdir -p $@

${BUILDIR}%.o:		${SRC_DIR}%.c ${HEADERS} Makefile
					${CC} ${INCLUDE} -c ${CFLAGS} $< -o $@
#
#bonus:				${BONUS}
#
#${BONUS}:
#					${MAKE} -C ${BONUSDIR}

clean:
					#${MAKE} clean -C ${BONUSDIR}
					${MAKE} clean -C ${LIBFTDIR}
					${MAKE} clean -C ${MLXDIR}
					${RM} ${BUILDIR}

fclean:				clean
					${MAKE} fclean -C ${LIBFTDIR}
					#${MAKE} fclean -C ${BONUSDIR}
					${RM} ${NAME}

re:					fclean all
