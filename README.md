# personal-projects

# My_Simple_Shell

My_Simple_Shell is bash-like shell program written in ANSI C. It allows for a single pipe between commands with '|', input redirection with '<' and '>', and editing of the path environment variable via '$PATH ='. 

It also maintains a history of previously entered commands, a list of aliases, and two unique environment variables.
The shell maintains a history file, msshrc_history, and will also initialize the alias list and PATH from a specifically formatted msshrc file.

  Environment variables:
  
      HISTCOUNT- the number of history entries that will be printed to the screen
      
      HISTFILECOUNT- the number of history entries that will be written to the shell's history file on close.
    
'history' prints out a numbered list of previously entered commands.
  '!!' will rerun the most recently entered command
  '!' and a valid integer will rerun the command entry with that integer.
  
'alias' prints out a list of the current aliases.
  'unalias' with an alias will remove that alias.
  
  The shell also recognizes &0 and &1 as shorcuts for standard out.
