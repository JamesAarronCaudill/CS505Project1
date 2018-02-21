/******************************

FILENAME: DAC_C++Implementation.cpp
AUTHOR: James Aarron Caudill & Kristina Gessel
CLASS: CS505G
DUE DATE: 03.01.18

ASSOCIATED FILES:
	input.txt
	output.txt
	README.text
    	Makefile

FILE DESCRIPTIONS:
	input.txt is a input file that can be that is an example of followable input,
	 this should be used with output.txt for expected outputs throughout the program.
	output.txt is a file of the expected output for input.text file
	README.txt is a file that describes this program in detail and lists any known issues.
    	Makefile is a file, that when 'make' is typed into the command line, in the appropriate directory
     	 the file will automatically compile the program.

THIS PROGRAM:
	This program is a security implementation of Discretionary Access Control similar to that of mySQL.
	 There will be built in commands

		TODO: ADD LIST OF BUILT IN COMMANDS HERE

DISTRIBUTION:
	This is under MIT License, for more information please view the associated License file.
	 This is however a school project, so turning this is as your own is forbidden.

******************************/

#define DACTokenBuffer 1024
#define DACTokDelim " \t\r\n\a"

int user_Logged_In = NULL;
int logCount;


/*
Array of Struct's for Acc Function, The max number of items in the log is 128.
*/
struct AccLog
{
char **UserName;
char **ActionLogged;
} AccessLogs[128];

/*
  List of builtin commands, followed by their corresponding functions.
*/
char *builtin_String[] = 
{
    "LOGIN",
    "LOGOUT",
    "GRANT",
    "CREATEUSER",
    "QUIT"
};

int (*builtin_Function[]) (char **) = 
{
    &DAC_Login,
    &DAC_Logout,
    &DAC_GrantPermision,
    &DAC_Create_User,
    &DAC_Quit
};

int DAC_num_builtins() {
    return sizeof(builtin_String) / sizeof(char *);
}

int DAC_Login(char **Tokens)
{
    


}


/*
This reads the input of the file for stdin
*/
char *DAC_read_line()
{
  char *line = NULL;
  ssize_t bufsize = 0; // Getline Will automatically allocate a buffer.
  getline(&line, &bufsize, stdin);
  return line;
}

/*
This is a line parser, it will split up the lines using strtok 
*/
char **DAC_split_line(char *input_Line)
{
  int buffer = DACTokenBuffer, position = 0;
  char **tokens = malloc(buffer * sizeof(char*));
  char *token;

  tokenCount = 0;

  token = strtok(input_Line, DACTokDelim);
  while (token != NULL) {
    tokens[position] = token;
    position++;
    tokenCount++;
    token = strtok(NULL, DACTokDelim);
    if(token == "EOF")
    {
        return 0;
    }
  }
  tokens[position] = NULL;
  return tokens;
}



void DAC_loop(void)
{
    char *input_Line;
    char **Tokens;
    int loop_Status;
  do {
        printf("Please type one of our Commands:\n");
	printf("
        input_Line = DAC_read_line();
        Tokens = DAC_split_line(input_Line);
        loop_Status = DAC_execute(Tokens);

	/*
	This will prepare the loop for the next run.
	*/
        free(input_Line);
        free(Tokens);
        } while (loop_Status);
}


/*
This will run into a loop. Called DAC_loop();
*/
int main()
{ 
  printf("Welcome to Discrectionary Access Control Simulation in C++!\n");
  DAC_loop();
  return EXIT_SUCCESS;
}
