# DITTO - Digital Image Tagging and Trading-Card Observer 

[Assets/Ditto.png]

### Group Members: Sam Lin, Devin Chen, Istab Rakin 

> [!WARNING] 
> This project is currently a work in progress and thus many features are either
> in an incomplete or broken state.  

## Build Instructions 

> [!IMPORTANT] 
> This project depends on OpenCV and that library must be installed on your
> computer to compile this project 

### Dependencies
```sh
Cmake
Make 
OpenCV # Must be accessible to CMAKE
``` 
 
### Compiling 

In the main directory (the directory with the CMakelists.txt) run: 

```sh
cmake . # creates a makefile for the project
make 
```

This would then output the binary `DITTO` which can then be run.

### Running the project 
> [!NOTE] 
> 
> 

```sh 
./DITTO <input_image> <template_image>
```

## Short Introduction 
Ditto is inspired by TAG grading. It is a trading card evaluation company that 
evaluates the quality of Pokémon cards and many different types of trading 
cards. The purpose of this project is to create a replica of TAG’s grading 
process and allow users to scan their own cards before evaluations through TAG 
by allowing the consumer to take a picture of their card and through some
computer vision algorithms, detect and trace defects to output a score on a 
scale of 1.0 through 10.0 (with 10 being the best). 

## Caveats 
Since Image Tagging usually requires a ring light and multiple cameras at 
different angles, we physically won't have as much data to work off of. So, this
would be a proof-of-concept for now (can we make a tagging system using easily 
accessible hardware) and fine tune it to an acceptable level? 


## Detecting the Card

In order to actually `TAG` the card, we do have to get a clean image of the card
itself. We initially set a standard card resolution of 330 by 440 pixels. 

[SAM.png]

Top (in order):    resizedImg, gray, blurred

Bottom (in order): edges, cornersImg, warpedImg
## References
- https://github.com/NolanAmblard/Pokemon-Card-Scanner/tree/main 
- https://github.com/hj3yoo/mtg_card_detector 
- https://www.youtube.com/watch?v=BLy_YF4nmqQ 
- OpenCV Documentation