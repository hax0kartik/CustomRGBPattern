# CustomRGBPattern
This is a patch for 3DS news module(0004013000003502) which changes the default blue notifictaion led color to some other color.

To use:

1. Extract the code.bin of news module(0004013000003502) using GM9
2. Download the precompiled binaries of the program from the release page.
3. Put the code.bin and the program in a new folder.
4. Download [armips](https://buildbot.orphis.net/armips/) from here.
5. Put it in the same folder as before.
6. Run the program and type in the rgb hex
7. Drag the `0004013000003502` folder from the `out` folder to `sdcard:/luma/titles`
8. Enable luma game patching.
9. ???
10. PROFIT!!!

To compile:-
`gcc main.c -o CustomRGBPattern.exe`