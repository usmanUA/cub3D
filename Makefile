
NAME 		:=	cub3d
ERRTXT		:=	error.txt
OBJSDIR		:=	build
INCSDIR		:=	include
SRCSDIR		:=	src
DEPSDIR		:=	.deps
LIBFTDIR	:=	libft
LIBVECDIR 	:=	vec
LIBFT		:=	$(LIBFTDIR)/libft.a
LIBVEC		:=	$(LIBVECDIR)/libvec.a

RM			:=	rm -rf
AR			:=	ar -rcs
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra
DEBUGFLAGS	=	-g -fsanitize=address
DEPFLAGS	=	-c -MT $$@ -MMD -MP -MF $(DEPSDIR)/$$*.d
SCREENCLR	:=	printf "\033c"
SLEEP		:=	sleep .1

MODULES		:=	main \
				init \
				parser \
				free \
				validator \
				get_next_line \

SOURCES 	= 	main.c \
			init_structs.c \
			map_validation.c \
			parsing_begins.c \
			free_mem.c \
			get_next_line.c \
			get_next_line_utils.c \

SOURCEDIR	:=	$(addprefix $(SRCSDIR)/, $(MODULES))
BUILDDIR	:=	$(addprefix $(OBJSDIR)/, $(MODULES))
DEPENDDIR	:=	$(addprefix $(DEPSDIR)/, $(MODULES))
SRCS		:=	$(foreach file, $(SOURCES), $(shell find $(SOURCEDIR) -name $(file)))
OBJS		:=	$(patsubst $(SRCSDIR)/%.c, $(OBJSDIR)/%.o, $(SRCS))
DEPS		:=	$(patsubst $(SRCSDIR)/%.c, $(DEPSDIR)/%.d, $(SRCS))
INCS	 	:=	$(foreach header, $(INCSDIR), -I $(header))
INCS	 	+=	$(foreach header, $(LIBVECDIR)/$(INCSDIR), -I $(header))
INCS	 	+=	$(foreach header, $(LIBFTDIR)/$(INCSDIR), -I $(header))

F			=	=====================================
B			=	\033[1m
T			=	\033[0m
G			=	\033[32m
V			=	\033[35m
C			=	\033[36m
R			=	\033[31m
Y			=	\033[33m

vpath %.c $(SOURCEDIR)

define cc_cmd
$1/%.o: %.c | $(BUILDDIR) $(DEPENDDIR)
	@if ! $(CC) -g $(INCS) $(DEPFLAGS) $$< -o $$@ 2> $(ERRTXT); then \
		printf "$(R)$(B)\nERROR!\n$(F)$(T)\n"; \
		printf "$(V)Unable to create object file:$(T)\n\n"; \
		printf "$(R)$(B)$$@$(T)\n"; \
		printf "$(Y)\n"; sed '$$d' $(ERRTXT); \
		printf "$(R)$(B)\n$(F)\nExiting...$(T)\n"; exit 1 ; \
	else \
		printf "$(C)$(B)☑$(T)$(V) $$<$ \n    $(C)⮑\t$(G)$(B)$$@$(T) \t\n"; \
	fi
endef

all: $(LIBFT) $(LIBVEC) $(NAME)

$(LIBFT):
	@make --quiet -C $(LIBFTDIR) all
	@make title

$(LIBVEC):
	@make --quiet -C $(LIBVECDIR) all
	@make title

$(NAME): $(OBJS)
	@$(CC) -g $(INCS) $^ $(LIBVEC) $(LIBFT) -o $@
	@make finish

debug: CFLAGS += $(DEBUGFLAGS)
debug: all

clean:
	@make --quiet -C $(LIBFTDIR) clean
	@make --quiet -C $(LIBVECDIR) clean
	@$(RM) $(OBJSDIR) $(DEPSDIR) $(ERRTXT)

fclean: clean
	@make --quiet -C $(LIBFTDIR) fclean
	@make --quiet -C $(LIBVECDIR) fclean
	@$(RM) $(NAME)

re: fclean all

title:
	@$(SCREENCLR) && printf "\n"
	@printf "$(C)                                    .--,-\`\`-.                   $(T)\n"
	@printf "$(C)  ,----..                  ,---,.  /   /     '.      ,---,      $(T)\n"
	@printf "$(C) /   /   \\         ,--,  ,'  .'  \\/ ../        ;   .'  .' \`\\    $(T)\n"
	@printf "$(C)|   :     :      ,'_ /|,---.' .' |\\ \`\`\\  .\`-    ',---.'     \\   $(T)\n"
	@printf "$(C).   |  ;. / .--. |  | :|   |  |: | \\___\\/   \\   :|   |  .\`\\  |  $(T)\n"
	@printf "$(C).   ; /--\`,'_ /| :  . |:   :  :  /      \\   :   |:   : |  '  |  $(T)\n"
	@printf "$(C);   | ;   |  ' | |  . .:   |    ;       /  /   / |   ' '  ;  :  $(T)\n"
	@printf "$(C)|   : |   |  | ' |  | ||   :     \\      \\  \\   \\ '   | ;  .  |  $(T)\n"
	@printf "$(C).   | '___:  | | :  ' ;|   |   . |  ___ /   :   ||   | :  |  '  $(T)\n"
	@printf "$(C)'   ; : .'|  ; ' |  | ''   :  '; | /   /\\   /   :'   : | /  ;   $(T)\n"
	@printf "$(C)'   | '/  :  | : ;  ; ||   |  | ; / ,,/  ',-    .|   | '\` ,/    $(T)\n"
	@printf "$(C)|   :    /'  :  \`--'   \\   :   /  \\ ''\\        ; ;   :  .'      $(T)\n"
	@printf "$(C) \\   \\ .' :  ,      .-./   | ,'    \\   \\     .'  |   ,.'        $(T)\n"
	@printf "$(C)  \`---\`    \`--\`----'   \`----'       \`--\`-,,-'    '---'\n"


finish:
	@printf "\n$(G)$(B)$(F)$(T)\n"
	@printf "$(C)╔═╗╦╔╗╔╦╔═╗╦ ╦╔═╗╔╦╗        $(V)$(B)$(NAME)$(T)\n"
	@printf "$(C)╠╣ ║║║║║╚═╗╠═╣║╣  ║║$(T)\n"
	@printf "$(C)╚  ╩╝╚╝╩╚═╝╩ ╩╚═╝═╩╝$(T)\n\n"

$(BUILDDIR) $(DEPENDDIR):
	@mkdir -p $@

$(DEPS):
	include $(wildcard $(DEPS))

$(foreach build, $(BUILDDIR), $(eval $(call cc_cmd, $(build))))

.PHONY: all debug clean fclean re title finish
