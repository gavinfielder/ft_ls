# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfielder <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/28 21:19:45 by gfielder          #+#    #+#              #
#    Updated: 2019/04/22 17:52:53 by gfielder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
CC=clang
CFLAGS=-Wall -Wextra -Werror
INC=-I inc
LIB=

PRINTF_SRC=ft_printf/api/ft_asprintf.c ft_printf/api/ft_printf.c ft_printf/api/ft_sbprintf.c \
	ft_printf/api/ft_snprintf.c ft_printf/api/ft_sprintf.c \
	ft_printf/api/ft_vdprintf.c ft_printf/api/ft_vsbprintf.c \
	ft_printf/api/ft_vsnprintf.c ft_printf/api/ft_vsprintf.c \
	ft_printf/api/ft_vprintf.c \
	ft_printf/backend/ftpf_expandler.c ft_printf/backend/ftpf_master.c \
	ft_printf/backend/checker_funcs/ftpf_checker_funcs_index.c \
	ft_printf/backend/checker_funcs/ftpf_checker_funcs_00_04.c \
	ft_printf/backend/checker_funcs/ftpf_checker_funcs_05_09.c \
	ft_printf/backend/checker_funcs/ftpf_checker_funcs_10_14.c \
	ft_printf/backend/checker_funcs/ftpf_checker_funcs_15_19.c \
	ft_printf/backend/checker_funcs/ftpf_checker_funcs_20_24.c \
	ft_printf/backend/checker_funcs/ftpf_checker_funcs_25_29.c \
	ft_printf/backend/expander_funcs/ftpf_percent_expander.c \
	ft_printf/backend/expander_funcs/ftpf_signed_int_expander.c \
	ft_printf/backend/expander_funcs/ftpf_unsigned_int_expander.c \
	ft_printf/backend/expander_funcs/ftpf_string_expander.c \
	ft_printf/backend/expander_funcs/ftpf_extension_expander.c \
	ft_printf/backend/expander_funcs/ftpf_hexlower_expander.c \
	ft_printf/backend/expander_funcs/ftpf_hexupper_expander.c \
	ft_printf/backend/expander_funcs/ftpf_octal_expander.c \
	ft_printf/backend/expander_funcs/ftpf_char_expander.c \
	ft_printf/backend/expander_funcs/ftpf_ptr_expander.c \
	ft_printf/backend/expander_funcs/ftpf_float_expander.c \
	ft_printf/backend/expander_funcs/ftpf_float_expander_utils.c \
	ft_printf/backend/expander_funcs/ftpf_floatl_expander.c \
	ft_printf/backend/expander_funcs/ftpf_floatl_expander_utils.c \
	ft_printf/backend/expander_funcs/ftpf_memory_and_binary_utils.c \
	ft_printf/backend/expander_funcs/ftpf_memory_expander.c \
	ft_printf/backend/expander_funcs/ftpf_binary_expander.c \
	ft_printf/backend/expander_funcs/ftpf_flt_expander_special.c \
	ft_printf/backend/getarg_funcs/ftpf_getarg_ints.c \
	ft_printf/backend/getarg_funcs/ftpf_getarg_main.c \
	ft_printf/backend/getarg_funcs/ftpf_getarg_other.c

SRC=other/ft_get_next_line.c \
	other/ft_putstr.c \
	other/ft_strcmp.c \
	other/ft_mem_1.c \
	other/ft_destroy_nullterm_ptrarray.c \
	other/ft_strsplit.c \
	other/ft_strstr.c \
	other/ft_putnbr.c \
	other/ft_litoa.c \
	other/ft_str_constructors.c \
	other/ft_mem_2.c \
	other/ft_strcpy.c \
	other/ft_putchar.c \
	other/ft_itoa.c \
	other/ft_str_aux.c \
	other/ft_strtrim.c \
	other/ft_strcat.c \
	other/ft_strjoin.c \
	other/ft_atoi.c \
	other/ft_print_hex.c \
	hat/ft_hat_toarr.c \
	hat/ft_hatdellf.c \
	hat/ft_hat_aux.c \
	hat/ft_hatinslf.c \
	hat/ft_hat_backend_1.c \
	hat/ft_hat.c \
	multistringer/ft_multistringer_aux.c \
	multistringer/ft_sbtostr.c \
	multistringer/ft_buffwriter.c \
	multistringer/ft_stringwriter.c \
	multistringer/ft_fildeswriter.c \
	multistringer/ft_multistringer.c \
	multistringer/ft_mswrite_nullterm.c \
	multistringer/ft_stringbuilder.c $(PRINTF_SRC)

OBJ:=$(shell echo $(SRC) | sed "s/\.c/\.o/g" | sed "s/ft_printf\//bin\//g" | sed "s/api\///g" | sed "s/backend\///g" | sed "s/expander_funcs\///g" | sed "s/checker_funcs\///g" | sed "s/getarg_funcs\///g" | sed "s/other\//bin\//g" | sed "s/hat\//bin\//g" | sed "s/multistringer\//bin\//g")

all: $(NAME)

$(NAME): bin
	@ar rs $(NAME) $(OBJ)  > /dev/null 2>&1
	@echo "Libft compiled."

bin: $(SRC)
	@mkdir -p bin
	@$(CC) -c $(CFLAGS) $(INC) $(SRC)
	@mv *.o bin/

clean:
	@rm -rf bin
	@echo "libft: Object files removed."

fclean:
	@rm -rf bin
	@rm -f $(NAME)
	@echo "libft: Object files and library removed."

re:
	@make fclean
	@make all
