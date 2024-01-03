<img src="git_utils/minishell_banner.png" alt="logo-so_long" style="width: 100%">
<img src="git_utils/minishell_logo.png" alt="logo-so_long" style="width: 100%">

---

### Level 3 - Common Core


**Lien du repo [ici](https://github.com/Asaped/Minishell).**

<div align="center">
<em>Dans notre projet "Minishell" à l'école 42, nous développons un programme de shell simplifié. Ce défi est crucial pour notre compréhension des processus et des descripteurs de fichiers. Notre but est de créer une version minimaliste de bash, nous immergeant ainsi dans les nuances de la programmation shell. Nous nous concentrons sur des aspects fondamentaux tels que la gestion des entrées de commandes, la manipulation des répertoires de fichiers, l'interprétation des variables d'environnement et l'implémentation de fonctionnalités essentielles comme la gestion des signaux et l'exécution des commandes. Ce projet représente une étape importante vers une compréhension approfondie de la programmation système, nous offrant une expérience pratique des concepts clés utilisés dans les environnements de shell Unix/Linux.</em>
</div>

<br>

---

<img src="git_utils/msh_plan.png" alt="minishell_plan" style="width: 100%">

---

# En détail

## Index

1. [Initialisation](#1-initialisation)
2. [Gestion des Signaux](#2-gestion-des-signaux)
3. [Prompt & Saisie Utilisateur](#3-prompt--saisie-utilisateur)
4. [Analyse Lexicale (Lexing)](#4-analyse-lexicale-lexing)
5. [Parsing (Analyse Syntaxique)](#5-parsing-analyse-syntaxique)
6. [Expansion des Variables](#6-expansion-des-variables)
7. [Exécution des Commandes](#7-exécution-des-commandes)
	- 7.1. [Exécution des Commandes Système](#71-exécution-des-commandes-système)
	- 7.2. [Exécution des Commandes Locales](#72-exécution-des-commandes-locales)
	- 7.3. [Exécution des Commandes Builtin](#73-exécution-des-commandes-builtin)
8. [Gestion des Redirections et des Pipes](#8-gestion-des-redirections-et-des-pipes)
9. [Nettoyage et Fin](#9-nettoyage-et-fin)

---

## 1. Initialisation

Fonction principale : ```init_data```

> Initialiser toutes les données essentielles du shell.

#### Initialisation de l'environnement (env)
La fonction crée une copie des variables d'environnement du système. Cette copie permet au shell de modifier ou de définir de nouvelles variables d'environnement sans affecter l'environnement global du système.
Utilise ```venv_count``` pour compter le nombre de variables d'environnement et ```ft_calloc``` pour allouer de la mémoire pour la copie.
Chaque variable est dupliquée avec ```ft_strdup``` pour garantir que le shell dispose de sa propre copie des variables d'environnement.

#### Configuration du niveau du shell (SHLVL)
La fonction ```increment_shlvl``` est appelée pour augmenter la valeur de la variable ```SHLVL```. Cela indique le niveau de shell imbriqué (combien de fois un shell a été lancé à l'intérieur d'un autre).
Si ```SHLVL``` n'est pas défini, il est initialisé à 1. Sinon, il est incrémenté.

#### Initialisation des répertoires de travail (wdir et old_wdir)
La fonction ```init_wds``` configure les répertoires de travail actuel et précédent.
Utilise ```getcwd``` pour obtenir le répertoire de travail actuel et le duplique dans ```wdir```.
Si la variable ```OLDPWD``` est définie, elle est utilisée pour initialiser ```old_wdir```; sinon, ```old_wdir``` est également défini sur le répertoire de travail actuel.

#### Initialisation des structures de commandes
Les pointeurs pour les tokens ```token```, l'entrée utilisateur ```user_input```, les commandes ```cmd```, et l'ID de processus ```pid``` sont initialisés à NULL ou à une valeur par défaut.

#### Gestion des erreurs :
Si une erreur se produit lors de l'initialisation (par exemple, une allocation mémoire échoue), le shell affiche un message d'erreur et termine l'exécution.

#### Fonctions Annexes
```venv_count``` : Compte le nombre de variables d'environnement. <br>
```increment_shlvl``` : Incrémente ou initialise la variable SHLVL. <br>
```init_wds``` : Initialise les répertoires de travail wdir et old_wdir. <br>

#### Flux de Contrôle
Appel de ```init_data```. <br>
↳ Allocation et initialisation de ```data->env```. <br>
↳ Appel de ```increment_shlvl``` pour ajuster ```SHLVL```. <br>
↳ Appel de ```init_wds``` pour configurer les répertoires de travail. <br>
↳ Initialisation des autres attributs de ```data``` (tokens, commandes, PID). <br>
↳ Gestion des erreurs et sortie en cas de défaillance. <br>

## Exemple Illustratif

- **Situation Initiale** : 
  L'utilisateur lance le shell Minishell.

- **Déroulement de l'Initialisation** :
  1. **Initialisation de l'Environnement** :
     - Le shell copie les variables d'environnement du système.
     - Exemple : `PATH`, `HOME`, `USER` sont copiées dans `data->env`.

  2. **Configuration du Niveau du Shell (SHLVL)** :
     - Si `SHLVL` n'est pas défini, il est initialisé à `1`.
     - Si `SHLVL` est défini (par exemple, à `2`), il est incrémenté à `3`.

  3. **Initialisation des Répertoires de Travail (wdir et old_wdir)** :
     - Supposons que l'utilisateur se trouve dans `/home/john/Desktop`.
     - `wdir` est défini sur `/home/john/Desktop`.
     - Si `OLDPWD` n'est pas défini, `old_wdir` est également défini sur `/home/john/Desktop`.

  4. **Initialisation des Structures de Commandes** :
     - `token`, `user_input`, `cmd`, et `pid` sont initialisés à `NULL` ou à des valeurs par défaut.

  5. **Gestion des Erreurs** :
     - Si une erreur se produit (par exemple, échec d'allocation mémoire), un message d'erreur est affiché et le shell se termine.

- **Résultat de l'Initialisation** :
  - Le shell est maintenant prêt à afficher le prompt et à accepter les commandes de l'utilisateur.
  - Les variables d'environnement et les répertoires de travail sont configurés et prêts à être utilisés.

## Conclusion
Ces fonctions préparent un environnement de shell fonctionnel. Elles établissent les bases sur lesquelles toutes les autres fonctionnalités du shell seront construites, y compris la gestion des variables d'environnement, la navigation dans le système de fichiers, et la préparation pour l'exécution des commandes.

<br>

---

<br>

## 2. Gestion des signaux

Fonctions principales : ```signals_on```, ```signals_off```, ```ignore_sigquit```

> Gérer les signaux pour interrompre ou contrôler les processus dans le shell.

#### Traitement des Signaux Interrupt ```SIGINT``` et Quit ```SIGQUIT```
Le shell doit être capable de gérer les interruptions utilisateur (comme Ctrl+C) et de quitter proprement lorsqu'on lui demande de terminer.

#### Fonction signals_on
> Activer la gestion des signaux spécifique au shell.

Utilise ```sigaction``` pour définir le gestionnaire de signal pour ```SIGINT```. <br>
Le gestionnaire de signal ```signal_reset_prompt``` est défini pour ```SIGINT```. Cette fonction réinitialise le prompt lorsque l'utilisateur appuie sur Ctrl+C. <br>
```ignore_sigquit``` est appelée pour ignorer le signal ```SIGQUIT```. Cela évite la fermeture brutale du shell lorsqu'un signal de quit est reçu.

#### Fonction signals_off
> Rétablir les gestionnaires de signal par défaut ou les désactiver.

Rétablit les gestionnaires de signal par défaut pour ```SIGINT``` et ```SIGQUIT```. <br>
Utilise ```signal_print_newline``` pour ```SIGINT```, qui imprime simplement une nouvelle ligne, rendant le shell moins intrusif.

#### Fonction signal_reset_prompt
> Écrit un saut de ligne pour assurer que le prompt s'affiche correctement après l'interruption. <br>

Utilise ```rl_on_new_line```, ```rl_replace_line``` et ```rl_redisplay``` de la bibliothèque ```readline``` pour réinitialiser la ligne de commande.

#### Fonction signal_print_newline
> Imprime simplement une nouvelle ligne pour préserver la structure du prompt.

Appelée lorsqu'un signal ```SIGINT``` est reçu. <br>

#### Fonction ```ignore_sigquit```
> Définit le gestionnaire de signal pour ```SIGQUIT``` à ```SIG_IGN``` (ignorer), empêchant le shell de se fermer brutalement.

#### Flux de Contrôle
```signals_on``` est appelée pour activer la gestion des signaux. <br>
Pendant l'exécution des commandes, ```signals_off``` peut être appelée pour désactiver ou modifier la gestion des signaux. <br>
Les fonctions ```signal_reset_prompt``` et ```signal_print_newline``` sont utilisées comme gestionnaires pour les signaux correspondants.

## Exemple Illustratif

- **Situation** : 
  L'utilisateur travaille dans le shell et interagit avec diverses commandes.

- **Signal SIGINT (Ctrl+C)** : 
  - Pendant la saisie d'une commande, l'utilisateur presse `Ctrl+C`.
  - **Comportement attendu** :
    - Le signal SIGINT est capté.
    - Le prompt est réinitialisé, affichant une nouvelle ligne.
    - La saisie en cours est interrompue sans fermer le shell.
  - **Exemple d'interaction** :
    ```
    john@shell:~/project $ long_running_command
    ^C
    john@shell:~/project $
    ```

- **Signal SIGQUIT (Ctrl+\\)** :
  - L'utilisateur exécute une commande et tente de l'interrompre avec `Ctrl+\`.
  - **Comportement attendu** :
    - Le signal SIGQUIT est ignoré.
    - Aucune sortie de core dump.
    - Le shell reste actif et la commande continue de s'exécuter.

- **Signal SIGINT pendant un processus enfant** :
  - L'utilisateur exécute une commande qui lance un processus enfant.
  - Pendant son exécution, l'utilisateur presse `Ctrl+C`.
  - **Comportement attendu** :
    - Le processus enfant reçoit le signal SIGINT et s'arrête.
    - Le shell affiche une nouvelle ligne de prompt sans quitter.

- **Sortie du Shell** :
  - L'utilisateur tape `exit` pour quitter le shell.
  - **Comportement attendu** :
    - Les signaux sont remis à leur état par défaut.
    - Le shell se termine proprement.

- **Résultat** : 
  - La gestion des signaux assure que le shell réagit correctement aux interruptions, permettant à l'utilisateur de contrôler le comportement des commandes et du shell lui-même.


## Conclusion
La gestion de signaux permet de gérer les interruptions de l'utilisateur de manière élégante et assure que le shell reste réactif et stable face aux actions inattendues de l'utilisateur. Cela inclut la gestion appropriée des signaux d'interruption et de fin, ainsi que la préservation de l'état et de l'affichage du shell.

<br>

---

<br>

# 3. Prompt & saisie utilisateur

#### Fonctions Principales : ```get_prompt```, ```readline```
> Afficher un prompt et lire la saisie de l'utilisateur.

#### Affichage du Prompt
```get_prompt```
> Afficher un prompt personnalisé indiquant l'état actuel du shell.

Utilise ```venv_value``` pour récupérer les valeurs des variables d'environnement comme ```USER```, ```SHLVL```, et ```PWD``` pour les intégrer dans le prompt. Son format : <br>

```
[USER] (SHLVL) ~/working/directory/with/PWD 
$>
```
Retourne la chaîne de caractères formatée représentant le prompt. Si par la suite les variables d'environnement sont remplacées ou supprimées, une valeur par defaut ou la valeur modifiée sera mise à jour sur le prompt.

#### Lecture de l'Entrée Utilisateur
```readline```
> Capturer la saisie de l'utilisateur.

Appel de la fonction ```readline``` de la bibliothèque GNU Readline. Cette fonction permet de saisir une ligne de texte avec diverses fonctionnalités telles que l'édition de ligne et l'historique des commandes. <br>

La saisie de l'utilisateur est renvoyée par ```readline``` et stockée dans la variable ```data->user_input``` pour un traitement ultérieur.

Les commandes saisies sont ajoutées à l'historique, permettant à l'utilisateur de rappeler les commandes précédentes avec les touches de navigation.


```get_prompt``` est appelée pour générer et afficher le prompt. <br>
↳ ```readline``` est utilisée pour lire la ligne de commande saisie par l'utilisateur. <br>
↳ La commande saisie est stockée pour un traitement ultérieur et ajoutée à l'historique des commandes.

## Exemple Illustratif

- **Situation** : 
  L'utilisateur est prêt à saisir une commande dans le shell.

- **Affichage du Prompt** : 
  - Supposons que l'utilisateur soit `john`, au niveau `SHLVL 2`, et dans le répertoire `/home/john/Desktop`.
  - Le prompt affiché sera :
    ```
    [john] (2) /home/john/Desktop
    $>
    ```

- **Saisie de l'Utilisateur** : 
  - L'utilisateur saisit la commande suivante :
    ```
    grep -r "search_term" .
    ```
  - Cette commande recherche le terme "search_term" récursivement dans le répertoire courant.

- **Traitement de la Saisie** : 
  - La saisie est capturée par `readline` et stockée dans `data->user_input`.
  - La commande est ajoutée à l'historique, permettant à l'utilisateur de la rappeler plus tard.

- **Interaction** :
  - L'utilisateur utilise les flèches du clavier pour naviguer dans l'historique des commandes.
  - Modifie la commande précédente en :
    ```
    grep -r "updated_term" .
    ```
  - Cette modification est également capturée par `readline`.

- **Résultat** : 
  - Le shell dispose désormais de la commande modifiée prête pour le traitement ultérieur.
  - Le prompt s'actualise en fonction des actions de l'utilisateur, reflétant les changements dans les variables d'environnement ou le répertoire de travail.


## Conclusion
Le prompt fournit un retour visuel essentiel, et la saisie de l'utilisateur détermine les actions que le shell doit effectuer. La bibliothèque GNU Readline enrichit cette interaction avec des fonctionnalités avancées comme l'édition de ligne et la gestion de l'historique.

<br>

---

<br>

# 4. Analyse Lexicale (Lexing)

#### Fonction Principale : `tokenization`

> Transforme l'entrée de l'utilisateur en une série de tokens pour un traitement ultérieur.

#### Processus de Tokenisation
- **Parcours de l'Entrée** : 
  - La fonction `tokenization` analyse la chaîne de caractères caractère par caractère.
  - Utilisation d'indicateurs d'état (`SQ`, `DQ`, `DEFAULT`) pour gérer les quotes et le contexte général.

#### Identification des Tokens
- **Types de Tokens** : 
  - Reconnaissance des mots (`WORD`), variables (`VAR`), opérateurs de pipe (`PIPE`), types de redirections (`INPUT`, `TRUNC`, `HEREDOC`, `APPEND`), et espaces (`SPACES`).
- **Changement d'État** : 
  - La fonction `set_status` gère les transitions entre les états de quotation et l'état par défaut.
- **Sauvegarde des Tokens** : 
  - Utilise `save_word_or_sep` pour enregistrer des mots ou des opérateurs dans la liste de tokens.

#### Création et Ajout de Tokens
- **Création** : 
  - Les nouveaux tokens sont créés avec `create_token`.
- **Ajout à la Liste** : 
  - Les tokens sont ajoutés à la liste en utilisant `add_token`.

#### Gestion des Séparateurs et Redirections
- **Traitement des Séparateurs** : 
  - La fonction `save_separator` gère les différents types de séparateurs et redirections, les ajoutant à la liste de tokens.

#### Gestion des Quotations
- **Impact sur la Tokenisation** : 
  - Les quotations modifient la manière dont l'entrée est tokenisée, en protégeant certains caractères ou en changeant leur signification.
- **Traitement des Quotations** : 
  - La fonction `tokenization` prend en compte les états de quotation pour former correctement les tokens.

#### Fonctions Annexes
- **`set_status`** : Transition entre les états de quotation et l'état par défaut.
- **`save_word_or_sep`** : Enregistre les mots ou séparateurs identifiés.
- **`save_separator`** : Gère les différents types de séparateurs et redirections.
- **`create_token`** : Crée un nouveau token.
- **`add_token`** : Ajoute un token à la liste.

#### Flux de Contrôle
1. L'entrée utilisateur est passée à `tokenization`.
2. La fonction identifie et catégorise les différents tokens.
3. Les tokens identifiés sont créés et ajoutés à la liste de tokens.
4. Les quotes et autres caractères spéciaux sont traités pour garantir une tokenisation correcte.

## Exemple Illustratif

- **Entrée Utilisateur** : 
  - `"cat file.txt | grep 'Jan' > jan_files.txt"`
- **Processus de Tokenisation** :
  1. `cat` identifié comme `WORD`.
  2. `file.txt` identifié comme `WORD`.
  3. `|` identifié comme `PIPE`.
  4. `grep` identifié comme `WORD`.
  5. `'Jan'` identifié comme `WORD` avec gestion des quotes.
  6. `>` identifié comme `TRUNC`.
  7. `jan_files.txt` identifié comme `WORD`.
- **Résultat de la Tokenisation** :
  - Une série de tokens représentant chaque élément de la commande.

## Conclusion
L'analyse lexicale est cruciale pour interpréter correctement la ligne de commande de l'utilisateur. Elle segmente l'entrée brute en une série de tokens structurés, facilitant ainsi les étapes de parsing et d'exécution. Une attention particulière est portée à la gestion des quotes et des séparateurs pour assurer une interprétation précise des commandes.

<br>

---

<br>

# 5. Parsing (Analyse Syntaxique)

#### Fonction Principale : `create_commands`

> Analyser les tokens pour former des commandes structurées prêtes à être exécutées.

#### Processus de Parsing
- **Construction des Commandes** : 
  - La fonction `create_commands` décompose la liste de tokens en commandes individuelles.
  - Chaque commande est une structure `t_cmd` contenant le nom de la commande, les arguments, les informations de redirection et de pipe.

#### Étapes de Parsing
- **Début du Parsing** : 
  - Démarre avec le premier token de la liste et le parse jusqu'à ce que tous les tokens soient traités.
- **Traitement des Tokens** : 
  - Selon le type de token (mot, variable, opérateur, etc.), différentes actions sont effectuées pour construire la commande.

#### Parsing des Différents Éléments
- **Mots et Variables (`WORD`, `VAR`)** : 
  - Utilise `parse_word` pour traiter les tokens de type mot et variable, qui deviennent les noms des commandes ou leurs arguments.
- **Redirections (`INPUT`, `TRUNC`, `HEREDOC`, `APPEND`)** : 
  - Des fonctions spécifiques comme `parse_input`, `parse_trunc`, `parse_heredoc`, et `parse_append` sont utilisées pour gérer les redirections.
- **Pipes (`PIPE`)** : 
  - `parse_pipe` est utilisé pour traiter les opérateurs de pipe, marquant le début d'une nouvelle commande et la liaison avec la précédente.

#### Construction de la Structure de Commande
- **Allocation de Commandes** : 
  - Crée une nouvelle structure `t_cmd` pour chaque nouvelle commande identifiée.
- **Ajout d'Arguments** : 
  - Les tokens suivants le nom de la commande sont traités comme des arguments et ajoutés à la commande.
- **Gestion des Pipes et Redirections** : 
  - Les informations de pipe et de redirection sont ajoutées à la structure de la commande pour gérer l'entrée/sortie lors de l'exécution.

#### Fonctions Annexes
- **`parse_word`** : Traite les tokens de type mot et variable.
- **`parse_input`, `parse_trunc`, `parse_heredoc`, `parse_append`** : Gèrent différents types de redirections.
- **`parse_pipe`** : Traite les opérateurs de pipe.
- **`cmd_creator`, `cmd_adder`** : Créent et ajoutent des structures de commande.

#### Flux de Contrôle
1. L'entrée tokenisée est passée à `create_commands`.
2. La fonction parcourt chaque token et détermine son rôle dans la construction de la commande.
3. Les commandes sont construites et les tokens correspondants sont traités.
4. Les structures de commande complètes sont prêtes pour l'exécution.

## Exemple Illustratif

- **Entrée Utilisateur** : 
  - `"ls -l | grep 'Jan' > jan_files.txt"`
- **Tokens Générés** :
  - `ls`, `-l`, `|`, `grep`, `'Jan'`, `>`, `jan_files.txt`
- **Processus de Parsing** :
  1. `ls` et `-l` sont interprétés comme commande et argument.
  2. Le pipe (`|`) indique une nouvelle commande.
  3. `grep 'Jan'` est la nouvelle commande avec un argument.
  4. La redirection (`>`) indique que la sortie de `grep` doit être écrite dans `jan_files.txt`.
- **Résultat du Parsing** :
  - Deux commandes structurées :
    1. Commande `ls -l` avec un pipe de sortie.
    2. Commande `grep 'Jan'` avec une redirection de sortie vers `jan_files.txt`.


## Conclusion
Le parsing est essentiel pour transformer l'entrée tokenisée en commandes structurées. Cette étape analyse la syntaxe et organise les tokens en commandes cohérentes, comprenant les noms de commandes, les arguments, et les configurations de redirection et de pipe. Cette organisation est cruciale pour l'exécution précise des commandes par le shell.

<br>

---

<br>

# 6. Expansion des Variables

#### Fonction Principale : `var_expander`

> Expande les variables et remplace les références de variables par leurs valeurs.

#### Objectif
L'expansion des variables est une étape essentielle dans l'interprétation des commandes dans un shell. Elle consiste à transformer les références de variables, comme `$HOME` ou `$PATH`, en leurs valeurs actuelles. Ce processus est crucial pour personnaliser l'exécution des commandes en fonction de l'environnement de l'utilisateur.

#### Processus d'Expansion :

1. **Identification des Variables** :
   - Le processus commence par parcourir chaque token généré pendant l'analyse lexicale.
   - Chaque token est examiné pour déterminer s'il contient une référence de variable (typiquement précédée par `$`).
   - `var_identifier` est utilisée pour extraire le nom de la variable à partir de chaque token identifié comme `VAR`.

2. **Récupération des Valeurs des Variables** :
   - Pour chaque référence de variable, `venv_value` est appelée pour rechercher la valeur actuelle de cette variable dans l'environnement du shell.
   - Si une variable d'environnement n'est pas définie, la référence est remplacée par une chaîne vide, évitant ainsi toute interruption du processus de commande.

3. **Remplacement des Références de Variables** :
   - `var_replacer` prend le relais pour remplacer chaque référence de variable dans le token par sa valeur correspondante.
   - Si une variable est suivie d'autres caractères ou chaînes (comme `$VARtext`), l'expansion est soigneusement réalisée pour s'assurer que seule la partie variable est expansée.

4. **Gestion des Cas Spéciaux** :
   - Un traitement spécifique est appliqué pour des cas comme `$?`, qui est remplacé par le statut de sortie de la dernière commande exécutée.
   - Les références de variables atypiques, comme un `$` suivi immédiatement d'un chiffre ou de caractères non valides, ne sont pas expansées.

#### Fonctions Annexes :
- `var_identifier` : Détecte et isole le nom de la variable dans un token.
- `venv_value` : Obtient la valeur actuelle d'une variable depuis l'environnement du shell.
- `var_replacer` : Effectue le remplacement effectif de la référence de la variable par sa valeur.

## Exemple Illustratif :

- **Situation Initiale** :
  L'utilisateur entre la commande : `echo $HOME`.
  Imaginons que `HOME` soit défini à `/home/john`.

- **Déroulement de l'Expansion** :
  1. `$HOME` est identifié comme une référence de variable.
  2. La valeur de `HOME` est récupérée : `/home/john`.
  3. `$HOME` dans la commande est remplacé par `/home/john`.

- **Résultat de l'Expansion** :
  La commande initiale `echo $HOME` est transformée en `echo /home/john`.
  L'exécution de cette commande modifiée affichera le chemin du répertoire personnel de l'utilisateur.

## Conclusion

L'expansion des variables est une fonctionnalité clé qui ajoute une couche de personnalisation et de flexibilité aux commandes du shell. Elle permet aux utilisateurs d'intégrer des éléments dynamiques de leur environnement dans les commandes, augmentant ainsi la puissance et l'adaptabilité du shell. Cette étape est donc indispensable pour un fonctionnement interactif et efficace du shell, adapté aux besoins spécifiques de chaque utilisateur.

<br>

---

<br>

# 7. Exécution des Commandes

#### Fonction Principale : `execute`

> Prend en charge l'exécution des commandes après le parsing et l'expansion.

#### Objectif
L'exécution des commandes est la phase finale où le shell exécute réellement la commande interprétée, qu'elle soit interne (builtin), externe (system) ou locale.

#### Processus d'Exécution :

1. **Préparation à l'Exécution** :
   - `exec_prep` prépare l'environnement pour l'exécution en vérifiant si la commande est valide et en configurant les pipes si nécessaire.

2. **Exécution des Builtin** :
   - Si la commande est une commande interne (builtin), comme `cd` ou `echo`, elle est exécutée directement par `execute_builtin`.
   - Ces commandes ne nécessitent pas la création de processus supplémentaires.

3. **Exécution des Commandes Système** :
   - Si la commande n'est pas un builtin, `execute_system` cherche la commande dans les chemins spécifiés par `$PATH` et exécute la commande externe.
   - La création de processus est gérée par `fork`, et l'exécution proprement dite est réalisée par `execve`.

4. **Gestion des Pipes et Redirections** :
   - `set_pipe_fds` et `io_redirecter` sont utilisées pour gérer les redirections d'entrée/sortie et les communications entre processus via des pipes.
   - Les pipes permettent de connecter la sortie d'une commande à l'entrée de la suivante, tandis que les redirections redirigent l'entrée/sortie vers ou depuis des fichiers.

5. **Nettoyage et Fermeture** :
   - Après l'exécution, un nettoyage est effectué pour s'assurer que tous les descripteurs de fichiers et ressources sont correctement fermés et libérés.

#### Fonctions Annexes :
- `exec_prep` : Prépare l'environnement pour l'exécution.
- `execute_builtin` : Exécute les commandes internes.
- `execute_system` : Exécute les commandes système via `execve`.
- `set_pipe_fds` : Configure les descripteurs de fichiers pour les pipes.
- `io_redirecter` : Gère les redirections d'entrée/sortie.

## 7.1 Exécution des Commandes Système

#### Fonction : `execute_system`

> Exécute les commandes non-builtin, généralement des commandes système externes.

#### Description
Cette fonction est responsable de l'exécution des commandes qui ne sont pas intégrées dans le shell (non-builtin). Ces commandes incluent la plupart des commandes UNIX/Linux standard telles que `ls`, `grep`, `cat`, etc.

#### Processus d'Exécution :
1. **Vérification de la Commande** :
   - Confirme que la commande n'est pas un builtin et qu'elle existe dans les chemins spécifiés par `$PATH`.
   - Si la commande n'est pas trouvée, une erreur est renvoyée.

2. **Création de Processus** :
   - Utilise `fork` pour créer un nouveau processus.
   - Dans le processus enfant, `execve` est appelé avec le chemin de la commande et ses arguments.

3. **Gestion des Erreurs** :
   - Si `execve` échoue (par exemple, en raison de permissions insuffisantes), un message d'erreur est affiché.

## Exemple de Commande Système :

- **Commande** : `ls -l`
- **Exécution** :
  - `ls` est identifié comme une commande système.
  - Un nouveau processus est créé.
  - `execve` est appelé pour exécuter `ls` avec l'argument `-l`.
- **Résultat** :
  - Affiche la liste détaillée des fichiers et dossiers dans le répertoire courant.

---

## 7.2 Exécution des Commandes Locales

#### Fonction : `execute_local`

> Gère l'exécution des commandes locales ou des scripts.

#### Description
La fonction traite les commandes qui ne sont ni des builtin ni des commandes système standard, généralement des scripts ou des exécutables locaux.

#### Processus d'Exécution :
1. **Vérification du Chemin** :
   - Confirme si la commande commence par `./` ou `/`, indiquant un chemin relatif ou absolu.
   - Vérifie l'existence et l'exécutabilité du fichier.

2. **Création de Processus** :
   - Utilise `fork` pour créer un processus enfant.
   - `execve` est appelé dans le processus enfant pour exécuter le fichier exécutable ou le script.

3. **Gestion des Erreurs** :
   - Si le fichier n'existe pas ou n'est pas exécutable, un message d'erreur est affiché.

## Exemple de Commande Locale :

- **Commande** : `./monscript.sh`
- **Exécution** :
  - Le shell identifie `./monscript.sh` comme un script ou un exécutable local.
  - Un processus enfant est créé pour exécuter le script.
- **Résultat** :
  - Le script `monscript.sh` est exécuté et ses résultats sont affichés.

---

## 7.3 Exécution des Commandes Builtin

#### Fonction : `execute_builtin`

> Exécute les commandes intégrées (builtin) au shell.

#### Description
Gère l'exécution des commandes qui sont directement intégrées dans le shell, telles que `cd`, `echo`, `exit`, etc.

#### Processus d'Exécution :
1. **Identification des Builtin** :
   - Détecte si la commande est un builtin en se référant à une liste prédéfinie.

2. **Exécution Directe** :
   - Appelle la fonction correspondante au builtin (par exemple, `builtin_cd` pour `cd`).

3. **Gestion des Retours** :
   - Les commandes builtin retournent généralement un statut d'exécution qui est traité par le shell.

## Exemple de Commande Builtin :

- **Commande** : `cd /home`
- **Exécution** :
  - `cd` est identifié comme un builtin.
  - La fonction `builtin_cd` est appelée avec `/home` comme argument.
- **Résultat** :
  - Le shell change le répertoire courant pour `/home`.

## Conclusion

L'exécution des commandes est le cœur du fonctionnement d'un shell. Elle transforme les commandes analysées et préparées en actions concrètes, interagissant avec le système d'exploitation et d'autres programmes. Cette phase est cruciale pour la réalisation effective des tâches demandées par l'utilisateur, rendant le shell un outil puissant et interactif.

<br>

---

<br>

# 8. Gestion des Redirections et des Pipes

#### Fonctions Principales : `io_redirecter`, `set_pipe_fds`, `close_pipe_fds`

> Gérer les redirections d'entrée/sortie et les pipes entre les commandes.

#### Objectif
La gestion des redirections et des pipes est essentielle pour contrôler le flux de données entre les commandes, les fichiers et les périphériques d'entrée/sortie.

#### Redirections d'Entrée/Sortie
##### Processus de Redirection :
1. **Identification des Redirections** :
   - Analyse de la ligne de commande pour identifier les symboles de redirection (`<`, `>`, `>>`).
   - Extraction des noms de fichiers associés aux redirections.

2. **Configuration des Descripteurs de Fichier** :
   - `io_redirecter` modifie les descripteurs de fichier standard (`stdin`, `stdout`) pour rediriger l'entrée et la sortie.
   - Pour les redirections de sortie (`>`, `>>`), les fichiers sont ouverts en mode écriture/troncature ou écriture/ajout.
   - Pour les redirections d'entrée (`<`), le fichier spécifié est ouvert en mode lecture.

3. **Duplication des Descripteurs de Fichier** :
   - Utilisation de `dup2` pour rediriger `stdin` et/ou `stdout` vers les fichiers appropriés.

4. **Restauration des Descripteurs de Fichier** :
   - Après l'exécution de la commande, `io_restorer` est appelé pour restaurer `stdin` et `stdout` à leurs états originaux.

#### Gestion des Pipes
##### Processus de Configuration des Pipes :
1. **Création de Pipes** :
   - `create_pipes` crée des pipes pour les commandes connectées par le symbole `|`.
   - Chaque pipe a deux descripteurs de fichier : un pour la lecture et un pour l'écriture.

2. **Connexion des Pipes aux Commandes** :
   - `set_pipe_fds` configure `stdin` et `stdout` de chaque commande pour lire et écrire dans les pipes appropriés.
   - Les données de sortie d'une commande sont passées à l'entrée de la commande suivante dans le pipeline.

3. **Fermeture des Pipes Inutilisés** :
   - `close_pipe_fds` ferme les extrémités des pipes qui ne sont pas utilisées par la commande en cours pour éviter les blocages et les fuites de ressources.

## Exemple Illustratif : Redirections et Pipes
- **Commande :** `cat input.txt | grep "error" > errors.txt`
- **Processus :**
  1. `cat input.txt` lit le contenu du fichier `input.txt`.
  2. La sortie de `cat` est passée à `grep "error"` via un pipe.
  3. `grep "error"` filtre les lignes contenant "error".
  4. La sortie filtrée est redirigée vers `errors.txt`.
- **Gestion des Descripteurs de Fichier :**
  - `cat` lit depuis `input.txt` (redirection d'entrée).
  - La sortie de `cat` est écrite dans le pipe.
  - `grep` lit depuis ce pipe (entrée).
  - La sortie de `grep` est écrite dans `errors.txt` (redirection de sortie).

## Conclusion

La gestion des redirections et des pipes est une fonctionnalité puissante des shells Unix/Linux. Elle permet aux utilisateurs de diriger et de manipuler le flux de données entre les commandes, les fichiers et les périphériques d'entrée/sortie, rendant les scripts shell et les commandes interactives plus flexibles et efficaces. Cette complexité requiert une gestion précise des descripteurs de fichier et une bonne compréhension des concepts d'entrée/sortie dans les systèmes Unix/Linux.

<br>

---

<br>

# 9. Nettoyage et Fin

#### Fonctions Principales : `free_data`, `exit_shell`

> Assurer le nettoyage des ressources et la fin correcte du shell.

#### Objectif
Nettoyer correctement toutes les ressources allouées et terminer l'exécution du shell de manière ordonnée.

#### Nettoyage des Ressources
##### Processus de Nettoyage :
1. **Libération de la Mémoire** :
   - `free_data` parcourt et libère toutes les structures allouées dynamiquement pendant l'exécution, y compris les tokens, les commandes, et les variables d'environnement.
   - Utilise des fonctions telles que `free_ptr`, `free_tab`, `cmds_clear`, et `clear_tokens` pour libérer la mémoire.

2. **Fermeture des Descripteurs de Fichier** :
   - Si des descripteurs de fichier sont ouverts pour les redirections ou les pipes, ils sont fermés pour éviter les fuites de ressources.
   - `close_fds` et `free_io` sont utilisées pour fermer et libérer les structures liées aux entrées/sorties.

3. **Nettoyage de l'Historique** :
   - Si activé, l'historique des commandes est nettoyé en appelant `rl_clear_history` de la bibliothèque Readline.

4. **Restauration des Signaux** :
   - Les gestionnaires de signaux sont remis à leurs états par défaut pour s'assurer qu'aucun comportement indésirable n'est conservé après la fermeture du shell.

#### Fin du Shell
- `exit_shell` est appelée pour terminer l'exécution du shell.
- Elle prend en argument un code de sortie (`exit_code`) qui est passé à la fonction `exit`.
- Ce code de sortie peut être utilisé pour communiquer l'état de la fermeture du shell aux processus parents ou aux scripts.

## Exemple Illustratif :
- Après avoir exécuté une série de commandes, l'utilisateur tape `exit`.
- Le shell commence le processus de nettoyage :
  - Libération de la mémoire allouée.
  - Fermeture des descripteurs de fichier ouverts.
  - Nettoyage de l'historique des commandes.
  - Restauration des gestionnaires de signaux.
- `exit_shell` est appelée avec le dernier statut de sortie (`g_exit_status`).
- Le shell se termine avec le code de sortie spécifié.

## Conclusion

Le nettoyage et la fin du shell sont des étapes cruciales pour garantir une fermeture propre et éviter les fuites de mémoire ou d'autres ressources système. Elles contribuent à la stabilité et à la fiabilité du shell, en s'assurant que toutes les ressources sont correctement libérées et que le shell se termine avec un statut clair. Ce processus est essentiel pour maintenir l'intégrité du système d'exploitation et prévenir les problèmes liés à une fermeture inappropriée ou à un nettoyage incomplet.

---

## Résultat

**(Evaluation à venir...)**

---

## Licence
This work is published under the terms of **[42 Unlicense](./LICENSE)**.
