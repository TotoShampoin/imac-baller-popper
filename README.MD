# Projet IMAC 2022: Baller Popper

[![Watch video](https://img.youtube.com/vi/iMXzQP_QsLo/maxresdefault.jpg)](https://www.youtube.com/watch?v=iMXzQP_QsLo)

[English edition](./README.EN.MD)

## Sommaire

- [Règles du jeu](#règles-du-jeu)
- [Compiler et exécuter](#compiler-et-exécuter)

## Règles du jeu

Sur l'écran apparaît des balles. Le joueur doit cliquer sur les balles pour les éclater.

Chaque balle rapporte 250 points, mais ce gain est multiplié de manière exponentielle si le joueur en éclate plusieurs en un seul clic.

Si le joueur clic sans que cela n'éclate de balle, une pénalité de 500 points est appliquée, et une nouvelle balle apparaît.

A la fin, le joueur peut voir son score final, ainsi que son taux de réussite (son pourcentage de bon clics).

## Compiler et exécuter

Entrer la commande pour compiler

```bash
make
```

Puis, pour exécuter

```bash
cd bin
./ballers
```

Pour jouer sur une fenêtre plus grande, mettre en argument un multiplicateur

```bash
# Pour une fenêtre 2 fois plus grande:
./ballers 2
```
