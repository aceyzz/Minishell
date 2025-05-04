<img src="git_utils/banner.png" alt="logo-minishell" style="width: 100%">

<br>

---

<br>

<details>
<summary>FRENCH VERSION</summary>

<br>

<div align="center">
<em>Dans notre projet "Minishell" à l'école 42, nous développons un programme de shell simplifié. Ce défi est crucial pour notre compréhension des processus et des descripteurs de fichiers. Notre but est de créer une version minimaliste de bash, nous immergeant ainsi dans les nuances de la programmation shell. Nous nous concentrons sur des aspects fondamentaux tels que la gestion des entrées de commandes, la manipulation des répertoires de fichiers, l'interprétation des variables d'environnement et l'implémentation de fonctionnalités essentielles comme la gestion des signaux et l'exécution des commandes. Ce projet représente une étape importante vers une compréhension approfondie de la programmation système, nous offrant une expérience pratique des concepts clés utilisés dans les environnements de shell Unix/Linux.</em>
</div>

<br>

---

## Contributors

- [#Chrstphr_0o](https://github.com/ChrstphrChevalier) - Lien vers l'intra [ici](https://profile.intra.42.fr/users/waziz)
- [aceyzz](https://github.com/aceyzz) - Lien vers l'intra [ici](https://profile.intra.42.fr/users/cedmulle)

---

<br>

<img src="git_utils/msh_plan.png" alt="minishell_plan" style="width: 100%">

---

## Utilisation

- Verification de la norme du projet:
```bash
make norme
```
- Compilation du projet:
```bash
make
```
- Exécution du projet:
```bash
./minishell
```
- Nettoyage des fichiers de compilation:
```bash
make clean
```
- Nettoyage de tous les fichiers générés:
```bash
make fclean
```
- Nettoyage et recompilation du projet:
```bash
make re
```

---

## Features

#### Gestion des commandes internes (echo, cd, pwd, export, unset, env, exit) :
Le programme Minishell doit pouvoir exécuter ces commandes internes de base.
#### Gestion des commandes externes :
Le programme Minishell doit pouvoir exécuter des commandes externes en utilisant les fonctions système appropriées.
#### Gestion des variables d'environnement :
Le programme Minishell doit pouvoir gérer les variables d'environnement, y compris leur création, modification et suppression.
#### Gestion des signaux (Ctrl-C, Ctrl-D) :
Le programme Minishell doit pouvoir gérer les signaux Ctrl-C et Ctrl-D, en interrompant ou en quittant le shell respectivement.
#### Gestion des erreurs :
Le programme Minishell doit pouvoir gérer les erreurs et afficher des messages d'erreur appropriés en cas de problème.
#### Gestion des redirections (>, >>, <) : 
Le programme Minishell doit pouvoir gérer les redirections de flux de données, en redirigeant la sortie vers un fichier ou en utilisant un fichier comme entrée.
#### Gestion des pipes (|) :
Le programme Minishell doit pouvoir gérer les pipes, permettant de connecter la sortie d'une commande à l'entrée d'une autre commande.
#### Gestion des expansions (", ', $) :
Le programme Minishell doit pouvoir gérer les expansions de variables, en remplaçant les variables par leur valeur correspondante.
#### Gestion des wildcards (*) et des quotes :
Le programme Minishell doit pouvoir gérer les caractères génériques (*) et les quotes, permettant de manipuler des fichiers et des chaînes de caractères de manière flexible.

---

## Architecure du projet
```shell
├── Bonus
│   ├── skip_quote_a.c         # Sauter les guillemets simples
│   ├── skip_quote_b.c         # Sauter les guillemets doubles
│   ├── skip_quote_middle.c    # Sauter les guillemets mixtes
│   ├── skip_utils.c           # Utilitaires pour sauter les guillemets
│   ├── wilcard_ab_utils.c     # Fonctions utilitaires pour les wildcards
│   ├── wildcard_base.c        # Logique de base des wildcards
│   ├── wildcards.c            # Gérer les wildcards
│   ├── wildcards_ab.c         # Gestion avancée des wildcards
│   └── wildcards_mult.c       # Support des multi-wildcards
├── Cmd
│   ├── cd.c                   # Changer de répertoire
│   ├── echo.c                 # Imprimer les arguments
│   ├── env.c                  # Imprimer l'environnement
│   ├── exec.c                 # Exécuter les commandes
│   ├── exit.c                 # Quitter le shell
│   ├── export.c               # Exporter des variables
│   ├── pwd.c                  # Imprimer le répertoire courant
│   ├── unset.c                # Désactiver des variables
│   └── value_return.c         # Utilitaires pour les valeurs de retour
├── FirstParse
│   ├── splitter_first_inits.c # Initialiser le découpage
│   ├── splitter_first_spaces.c # Gérer les espaces
│   ├── splitter_scnd_main.c   # Logique secondaire de découpage
│   ├── splitter_scnd_utils.c  # Fonctions utilitaires pour le découpage
│   ├── tokenizer_handlers.c   # Gestionnaires de tokenisation
│   ├── tokenizer_main.c       # Logique principale de tokenisation
│   └── tokenizer_utils.c      # Utilitaires pour la tokenisation
├── Include
│   └── minishell.h            # Fichier d'en-tête
├── Lexing
│   ├── access.c               # Vérifications d'accès aux fichiers
│   ├── access_exec.c          # Vérifications d'accès pour l'exécution
│   ├── access_utils.c         # Fonctions utilitaires pour l'accès
│   ├── cmd.c                  # Gestion des commandes
│   ├── cmd_utils.c            # Utilitaires pour les commandes
│   ├── cnf.c                  # Commande non trouvée
│   ├── cnf_utils.c            # Fonctions utilitaires pour CNF
│   ├── exit_code_utils.c      # Gestion des codes de sortie
│   ├── lexing.c               # Analyse lexicale
│   └── operator.c             # Gestion des opérateurs
├── Libft
├── Makefile                   # Construire le projet
├── Mnsh
│   ├── Initialisation.c       # Initialiser le shell
│   ├── cmd_without.c          # Gérer les commandes
│   ├── debug.c                # Outils de débogage
│   ├── input_pipe.c           # Gestion des pipes d'entrée
│   ├── mnsh_utils.c           # Utilitaires pour le shell
│   ├── reverse.c              # Inverser les chaînes
│   ├── signaux.c              # Gestion des signaux
│   └── take_input.c           # Gestion des entrées
├── Operators
│   ├── cmd_redirect.c         # Rediriger les commandes
│   ├── redirect_input_cmd.c   # Redirection d'entrée
│   └── redirect_stdout.c      # Redirection de sortie
├── Parsing
│   ├── convert.c              # Convertir les tokens
│   ├── convert_utils.c        # Fonctions utilitaires pour la conversion
│   ├── erase_quote.c          # Supprimer les guillemets
│   ├── new_arg.c              # Créer des arguments
│   ├── new_arg_utils.c        # Fonctions utilitaires pour les arguments
│   ├── parsing.c              # Analyser l'entrée
│   └── pid_utils.c            # Gestion des PID
├── Utils
│   ├── error.c                # Gestion des erreurs
│   ├── free.c                 # Libérer la mémoire
│   └── utils.c                # Utilitaires généraux
├── header.c                   # Logique de l'en-tête
└── minishell.c                # Programme principal
```

---

## Résultat

<img src="git_utils/grade.png" alt="grade" style="width: 25%">

---

## Licence
This work is published under the terms of **[42 Unlicense](./LICENSE)**.

</details>

<br>

---

<br>

<details>
<summary>ENGLISH VERSION</summary>

<br>

<div align="center">
<em>In our "Minishell" project at 42 school, we are developing a simplified shell program. This challenge is crucial for our understanding of processes and file descriptors. Our goal is to create a minimalist version of bash, immersing ourselves in the nuances of shell programming. We focus on fundamental aspects such as handling command inputs, manipulating file directories, interpreting environment variables, and implementing essential features like signal handling and command execution. This project represents an important step toward a deeper understanding of system programming, offering us hands-on experience with key concepts used in Unix/Linux shell environments.</em>
</div>

<br>

---

## Contributors

- [#Chrstphr_0o](https://github.com/ChrstphrChevalier) - Link to intra [here](https://profile.intra.42.fr/users/waziz)
- [aceyzz](https://github.com/aceyzz) - Link to intra [here](https://profile.intra.42.fr/users/cedmulle)

---

<br>

<img src="git_utils/msh_plan.png" alt="minishell_plan" style="width: 100%">

---

## Usage

- Project norm verification:
```bash
make norme
```
- Project compilation:
```bash
make
```
- Project execution:
```bash
./minishell
```
- Cleaning compilation files:
```bash
make clean
```
- Cleaning all generated files:
```bash
make fclean
```
- Cleaning and recompiling the project:
```bash
make re
```

---

## Features

#### Handling internal commands (echo, cd, pwd, export, unset, env, exit):
The Minishell program must be able to execute these basic internal commands.
#### Handling external commands:
The Minishell program must be able to execute external commands using appropriate system functions.
#### Handling environment variables:
The Minishell program must be able to manage environment variables, including their creation, modification, and deletion.
#### Handling signals (Ctrl-C, Ctrl-D):
The Minishell program must handle Ctrl-C and Ctrl-D signals, interrupting or exiting the shell respectively.
#### Error handling:
The Minishell program must handle errors and display appropriate error messages when issues arise.
#### Handling redirections (>, >>, <):
The Minishell program must handle data stream redirections, redirecting output to a file or using a file as input.
#### Handling pipes (|):
The Minishell program must handle pipes, allowing the output of one command to be connected to the input of another command.
#### Handling expansions (", ', $):
The Minishell program must handle variable expansions, replacing variables with their corresponding values.
#### Handling wildcards (*) and quotes:
The Minishell program must handle wildcards (*) and quotes, enabling flexible manipulation of files and strings.

---

## Project Architecture
```shell
├── Bonus
│   ├── skip_quote_a.c         # Skip single quotes
│   ├── skip_quote_b.c         # Skip double quotes
│   ├── skip_quote_middle.c    # Skip mixed quotes
│   ├── skip_utils.c           # Utilities for skipping quotes
│   ├── wilcard_ab_utils.c     # Utility functions for wildcards
│   ├── wildcard_base.c        # Basic logic for wildcards
│   ├── wildcards.c            # Handle wildcards
│   ├── wildcards_ab.c         # Advanced wildcard handling
│   └── wildcards_mult.c       # Support for multi-wildcards
├── Cmd
│   ├── cd.c                   # Change directory
│   ├── echo.c                 # Print arguments
│   ├── env.c                  # Print environment
│   ├── exec.c                 # Execute commands
│   ├── exit.c                 # Exit the shell
│   ├── export.c               # Export variables
│   ├── pwd.c                  # Print current directory
│   ├── unset.c                # Unset variables
│   └── value_return.c         # Utilities for return values
├── FirstParse
│   ├── splitter_first_inits.c # Initialize splitting
│   ├── splitter_first_spaces.c # Handle spaces
│   ├── splitter_scnd_main.c   # Secondary splitting logic
│   ├── splitter_scnd_utils.c  # Utility functions for splitting
│   ├── tokenizer_handlers.c   # Tokenization handlers
│   ├── tokenizer_main.c       # Main tokenization logic
│   └── tokenizer_utils.c      # Utilities for tokenization
├── Include
│   └── minishell.h            # Header file
├── Lexing
│   ├── access.c               # File access checks
│   ├── access_exec.c          # Execution access checks
│   ├── access_utils.c         # Utility functions for access
│   ├── cmd.c                  # Command handling
│   ├── cmd_utils.c            # Command utilities
│   ├── cnf.c                  # Command not found
│   ├── cnf_utils.c            # Utility functions for CNF
│   ├── exit_code_utils.c      # Exit code handling
│   ├── lexing.c               # Lexical analysis
│   └── operator.c             # Operator handling
├── Libft
├── Makefile                   # Build the project
├── Mnsh
│   ├── Initialisation.c       # Initialize the shell
│   ├── cmd_without.c          # Handle commands
│   ├── debug.c                # Debugging tools
│   ├── input_pipe.c           # Input pipe handling
│   ├── mnsh_utils.c           # Shell utilities
│   ├── reverse.c              # Reverse strings
│   ├── signaux.c              # Signal handling
│   └── take_input.c           # Input handling
├── Operators
│   ├── cmd_redirect.c         # Command redirection
│   ├── redirect_input_cmd.c   # Input redirection
│   └── redirect_stdout.c      # Output redirection
├── Parsing
│   ├── convert.c              # Convert tokens
│   ├── convert_utils.c        # Utility functions for conversion
│   ├── erase_quote.c          # Remove quotes
│   ├── new_arg.c              # Create arguments
│   ├── new_arg_utils.c        # Utility functions for arguments
│   ├── parsing.c              # Parse input
│   └── pid_utils.c            # PID management
├── Utils
│   ├── error.c                # Error handling
│   ├── free.c                 # Memory deallocation
│   └── utils.c                # General utilities
├── header.c                   # Header logic
└── minishell.c                # Main program
```

---

## Result

<img src="git_utils/grade.png" alt="grade" style="width: 25%">

---

## License
This work is published under the terms of **[42 Unlicense](./LICENSE)**.

</details>