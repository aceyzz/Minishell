<img src="git_utils/minishell_banner.png" alt="logo-so_long" style="width: 100%">
<img src="git_utils/minishell_logo.png" alt="logo-so_long" style="width: 100%">

---

### Level 3 - Common Core

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
