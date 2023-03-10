# Project IMAC 2022: Baller Popper

[![Watch video](https://img.youtube.com/vi/iMXzQP_QsLo/maxresdefault.jpg)](https://www.youtube.com/watch?v=iMXzQP_QsLo)

[Edition française](./README.MD)

## Summary

- [Game rules](#game-rules)
- [Compile and run](#compile-and-run)

## Game rules

Balls appear on screen. The player must click on the balls to pop them.

Each ball popped is worth 250 points, which is exponentially multiplied by the amount of balls popped in one click.

If the player clicks without popping any ball, a 500 points penalty is applied, and a new ball appears.

At the end of the game, the player sees their final score, and their success rate (the percentage of successful clicks).

## Compile and run

Enter the following command to compile

```bash
make
```

And then, to run the game

```bash
cd bin
./ballers
```

Tout play on a bigger window, add a multiplier as an argument

```bash
# For a 2 times bigger window:
./ballers 2
```
