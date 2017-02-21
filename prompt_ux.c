#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
/* figure out why this line isn't neccesary at some point
 * #include <editline/history.h>
*/
int main(int argc, char** argv)
{
	puts ("clispy ver -1");
	puts ("Ctrl+c to exit");
	while (1) 
 	{
		/*prompt & input combined via readline*/
		char* input = readline("lispc> ");	
		/*input -> history*/
		add_history(input);
		/*echo!*/
		printf("echoing %s\n", input);
		/*freedom*/
		free(input);
	}
	return 0;
}
