#ifndef MUSIC_HEADER_H
#define MUSIC_HEADER_H

#include "splashkit.h"
#include <string>
#include <vector>
using std::string;

// Initiate constants for piano key dimensions
const double WHITE_KEY_WIDTH = 50.0;
const double WHITE_KEY_HEIGHT = 200.0;
const double BLACK_KEY_WIDTH = 30.0;
const double BLACK_KEY_HEIGHT = 120.0;
const int MAX_PIANO_KEYS = 12;
const int TEXT_FONT_SIZE = 8;

// Enum for different note types
enum NoteType
{
    C,
    C_SHARP,
    D,
    D_SHARP,
    E,
    F,
    F_SHARP,
    G,
    G_SHARP,
    A,
    A_SHARP,
    B
};

// Enum for piano key colors
enum KeyColor
{
    WHITE,
    BLACK
};

// Enum to manage application states
enum AppState
{
    PLAYING_PIANO,
    GETTING_SAVE_FILENAME,
    SHOWING_LOAD_MENU,
    SHOWING_GUIDE,
    SHOWING_KEYBINDS
};

// Structure representing a singular piano key
struct PianoKey
{
    double x;          // Top-left x coordinate
    double y;          // Top-left y coordinate
    double width;      // Width of the key
    double height;     // Height of the key
    string label;      // Label for the key
    NoteType note;     // Chord note
    KeyColor color;    // White / Black key
    bool is_pressed;   // True if the key is currently pressed
    string sound_file; // Path to mp3 sound file
};

// Structure representing a recorded note event
struct NoteEvent
{
    NoteType note;
    unsigned int timestamp;
};

// Structure representing the entire piano
struct Piano
{
    PianoKey keys[MAX_PIANO_KEYS]; // Array of piano keys
    int key_count;                 // Number of keys in the piano
    double x;                      // Top-left x coordinate
    double y;                      // Top-left y coordinate
    double total_width;            // Total width of the piano
    double total_height;           // Total height of the piano

    // Recording and playback
    std::vector<NoteEvent> recording;
    bool is_recording;
    timer record_timer;
    bool is_playing;
    int next_note_index;

    // GUI state management
    AppState current_state;
    string text_input;
    std::vector<string> recording_files;
    
    // Guide button
    double guide_button_x;
    double guide_button_y;
    double guide_button_size;
    
    // Keybinds button
    double keybinds_button_x;
    double keybinds_button_y;
    double keybinds_button_size;
};

// ============================================================================
// PIANO CORE FUNCTIONS (piano_core.cpp)
// ============================================================================
key_code get_key_for_note(NoteType note);
string note_to_string(NoteType note);
string get_note_label(NoteType note);
void initialize_piano(Piano &piano);
void handle_keyboard_input(Piano &piano);
void press_key(PianoKey &key);
void release_key(PianoKey &key);
void play_note_sound(PianoKey &key);

// ============================================================================
// RECORDING FUNCTIONS (recording.cpp)
// ============================================================================
void start_recording(Piano &piano);
void stop_recording(Piano &piano);
void handle_recording(Piano &piano, NoteType note);

// ============================================================================
// PLAYBACK FUNCTIONS (playback.cpp)
// ============================================================================
void start_playback(Piano &piano);
void stop_playback(Piano &piano);
void handle_playback(Piano &piano);

// ============================================================================
// FILE I/O FUNCTIONS (file_io.cpp)
// ============================================================================
void initialize_recordings_directory();
void save_recording_to_file(const Piano &piano, const string &filename);
void load_recording_from_file(Piano &piano, const string &filename);
void list_available_recordings(Piano &piano);

// ============================================================================
// STATE MANAGEMENT FUNCTIONS (state_management.cpp)
// ============================================================================
void handle_playing_state(Piano &piano);
void handle_save_state(Piano &piano);
void handle_load_state(Piano &piano);
void handle_guide_state(Piano &piano);
void handle_keybinds_state(Piano &piano);

// ============================================================================
// GUI FUNCTIONS (gui.cpp)
// ============================================================================
void draw_piano_key(PianoKey &key);
void draw_piano(Piano &piano);
void draw_save_gui(const Piano &piano);
void draw_load_gui(const Piano &piano);
void draw_guide_button(const Piano &piano);
void draw_guide_menu(const Piano &piano);
void draw_keybinds_button(const Piano &piano);
void draw_keybinds_menu(const Piano &piano);

// ============================================================================
// GUI LOGIC FUNCTIONS (gui_logic.cpp)
// ============================================================================
void layout_piano(Piano &piano);
void handle_load_menu_input(Piano &piano);
bool is_guide_button_clicked(const Piano &piano);
bool is_keybinds_button_clicked(const Piano &piano);

#endif