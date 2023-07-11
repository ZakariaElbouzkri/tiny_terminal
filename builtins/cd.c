#include "../minishell.h"

//int chdir(const char *path);
// path begins with a '/'
// return 0 for succes -1 for error and set errno
int	main()
{
	int result = chdir("../lexer");
    
    if (result == 0) {
        printf("Directory change successful.\n");
    } else {
        perror("chdir");
        // You can access the specific error code using errno
        // perror("bash: ");
    }

    return 0;





}