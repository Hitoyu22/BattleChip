# BattleChip

Un jeu de bataille navale en C.

## Description

BattleChip est un jeu de bataille navale où vous pouvez placer des navires sur un plateau.

## Fonctionnalités

- Plateau de jeu personnalisable (5x5 à 26x26)
- Placement de navires
- Placement manuel ou automatique des navires

## Compilation

Utilisez la tâche "Compiler BattleChip" dans VS Code ou :

```
gcc -I./code/include ./code/src/game/game.c ./code/src/board/navire.c ./code/src/config/config.c -o ./executable/BattleChip.exe
```

## Utilisation

1. Compilez le projet
2. Exécutez `./executable/BattleChip.exe`
3. Choisissez la taille du plateau
4. Choisissez le nombre de navires
5. Choisissez le mode de placement (manuel/automatique)

## Structure du projet

- `code/src/` - Code source
- `code/include/` - Headers
- `executable/` - Exécutable compilé

## Types de navires

- Porte-avions (5 cases)
- Croiseur (4 cases)
- Destroyers (3 cases)
- Torpilleur (2 cases)
