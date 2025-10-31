#include "../include/music_header.h"
#include <string>

using std::string;

// Get keybinds for note
key_code get_key_for_note(NoteType note)
{
    switch (note)
    {
    case C:
        return A_KEY;
    case C_SHARP:
        return W_KEY;
    case D:
        return S_KEY;
    case D_SHARP:
        return E_KEY;
    case E:
        return D_KEY;
    case F:
        return F_KEY;
    case F_SHARP:
        return T_KEY;
    case G:
        return G_KEY;
    case G_SHARP:
        return Y_KEY;
    case A:
        return H_KEY;
    case A_SHARP:
        return U_KEY;
    case B:
        return J_KEY;
    default:
        return A_KEY;
    }
}

// Switches the note to a string type
string note_to_string(NoteType note)
{
    switch (note)
    {
    case C:
        return "C";
    case C_SHARP:
        return "C_SHARP";
    case D:
        return "D";
    case D_SHARP:
        return "D_SHARP";
    case E:
        return "E";
    case F:
        return "F";
    case F_SHARP:
        return "F_SHARP";
    case G:
        return "G";
    case G_SHARP:
        return "G_SHARP";
    case A:
        return "A";
    case A_SHARP:
        return "A_SHARP";
    case B:
        return "B";
    default:
        return "?";
    }
}

// Get display label for a note
string get_note_label(NoteType note)
{
    switch (note)
    {
    case C:
        return "C";
    case C_SHARP:
        return "C#";
    case D:
        return "D";
    case D_SHARP:
        return "D#";
    case E:
        return "E";
    case F:
        return "F";
    case F_SHARP:
        return "F#";
    case G:
        return "G";
    case G_SHARP:
        return "G#";
    case A:
        return "A";
    case A_SHARP:
        return "A#";
    case B:
        return "B";
    default:
        return "?";
    }
}

// Initializes the piano structure with keys and their properties (logic only)
void initialize_piano(Piano &piano)
{
    piano.key_count = 0;

    // Initialize white keys
    NoteType white_notes[] = {C, D, E, F, G, A, B};
    for (int i = 0; i < 7; i++)
    {
        PianoKey &key = piano.keys[piano.key_count];

        key.note = white_notes[i];
        key.color = WHITE;
        key.is_pressed = false;
        key.sound_file = "notes/" + note_to_string(white_notes[i]) + ".mp3";
        key.label = get_note_label(white_notes[i]);
        piano.key_count++;
    }

    // Initialize black keys
    NoteType black_notes[] = {C_SHARP, D_SHARP, F_SHARP, G_SHARP, A_SHARP};
    for (int i = 0; i < 5; i++)
    {
        PianoKey &key = piano.keys[piano.key_count];
        key.note = black_notes[i];
        key.color = BLACK;
        key.is_pressed = false;
        key.sound_file = "notes/" + note_to_string(black_notes[i]) + ".mp3";
        key.label = get_note_label(black_notes[i]);
        piano.key_count++;
    }

    // Initialize recording and playback state
    piano.is_recording = false;
    piano.is_playing = false;
    piano.record_timer = create_timer("record_timer");
    piano.next_note_index = 0;

    // Initialize GUI state
    piano.current_state = PLAYING_PIANO;
    piano.text_input = "";
}

// Handles keyboard input to press/release piano keys
void handle_keyboard_input(Piano &piano)
{
    for (int i = 0; i < piano.key_count; i++)
    {
        key_code mapped_key = get_key_for_note(piano.keys[i].note);

        if (key_down(mapped_key))
        {
            if (!piano.keys[i].is_pressed)
            {
                press_key(piano.keys[i]);

                // Record the note if recording is active
                if (piano.is_recording)
                {
                    handle_recording(piano, piano.keys[i].note);
                }
            }
        }
        else
        {
            if (piano.keys[i].is_pressed)
            {
                release_key(piano.keys[i]);
            }
        }
    }
}

// Sets the key to pressed state and plays its sound
void press_key(PianoKey &key)
{
    key.is_pressed = true;
    play_note_sound(key);
}

// Plays the sound associated with the piano key
void play_note_sound(PianoKey &key)
{
    string note_name = note_to_string(key.note);
    if (!has_sound_effect(note_name))
    {
        load_sound_effect(note_name, key.sound_file);
    }

    if (has_sound_effect(note_name))
    {
        play_sound_effect(note_name);
    }
}

// Sets the key to released state
void release_key(PianoKey &key)
{
    key.is_pressed = false;
}