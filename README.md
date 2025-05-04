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

## Result

<img src="git_utils/grade.png" alt="grade" style="width: 25%">

---

## License
This work is published under the terms of **[42 Unlicense](./LICENSE)**.

</details>