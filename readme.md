# 🎹 PIANO MUSIC APP

**Author:** Lim Khai Xiang  
**Version:** v9
**Date:** 27 / 10 / 2025

---

## 📋 Table of Contents
- ## [Details](#a-details)
  - [Description](#description)
  - [Features](#features)
  - [KeyBinds](#keybinds)
- ## [Instructions](#b-instructions)
  - [Run Default Program](#run-default-program)
  - [Run Test](#run-test)

---

## 📖 A. Details

### 📝 Description
A piano app that is tailored for digital use and can be run through C++ language and SplashKit and Standard libraries.

### ✨ Features
A full fledge piano octave that is designed with beautiful graphics which engages users interaction and learning attributes. The piano keys and notes ranges from the natural chords of C, D, E, F, G, A, B and the sharp and flat chords of C#, D#, F#, G#, A#. This program also has a recording a playback
feature where the user can save and load the recordings.

### ⌨️ KeyBinds

#### 🎵 Natural Notes
1. **A Key** : C Note
2. **S Key** : D Note
3. **D Key** : E Note
4. **F Key** : F Note
5. **G Key** : G Note
6. **H Key** : A Note
7. **J Key** : B Note

#### ♯ Sharp and Flat Notes
1. **W Key** : C# Note
2. **E Key** : D# Note
3. **T Key** : F# Note
4. **Y Key** : G# Note
5. **U Key** : A# Note

---

## 🚀 B. Instructions

### Run Through Terminal
```bash
./run.bat
```
```bash
clang++ src/main_music.cpp src/piano_core.cpp src/recording.cpp src/playback.cpp src/file_io.cpp src/state_management.cpp src/gui_logic.cpp src/gui.cpp -l SplashKit -o piano
```

### Run From File Explorer
```folder
double click run.bat folder
```