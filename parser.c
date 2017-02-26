/*standard*/
#include <stdio.h>
#include <stdlib.h>
/*installed*/
#include <editline/readline.h>
/*local*/
#include "mpc.h"


int main(int argc, char** argv)
{
	/*parse stuff*/
	mpc_parser_t* Num 	= mpc_new("num");
	mpc_parser_t* Optor	= mpc_new("optor");
	mpc_parser_t* Expr	= mpc_new("expr");
	mpc_parser_t* Lispc	= mpc_new("lispc");

	/* Langauge defined */
	mpca_lang(MPCA_LANG_DEFAULT,
	/* regex */
	"						\
		num	: /-?[0-9]+/ ;			\
		optor	: '+' | '-' | '*' | '/';	\
		expr	: <num> | '('<optor> <expr>+')';\
		lispc	: /^/ <optor> <expr>+ /$/;	\
	",
	Num, Optor, Expr, Lispc);

	puts ("clispy ver 0.0.6-math");
	puts ("Ctrl+c to exit");
	
	while (1) 
 	{
		char* input = readline("lispc> ");
		add_history(input);
		puts(input);
		mpc_result_t r;
		if (mpc_parse("<stdin>", input, Lispc, &r))
		{
			/*success conditioni: print AST*/
			mpc_ast_print(r.output);
			mpc_ast_delete(r.output);
		}
		else
		{	/*error!*/
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}
		free(input);
	}
	
	mpc_cleanup(4,Num,Optor,Expr,Lispc);
	return 0;
}
