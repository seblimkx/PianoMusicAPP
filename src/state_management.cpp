#include "../include/music_header.h"
#include <string>

using std::string;

// Handle logic for PLAYING_PIANO state
void handle_playing_state(Piano &piano)
{
    // Handle normal piano playing
    handle_keyboard_input(piano);
    handle_playback(piano);

    // Check for recording controls
    if (key_typed(R_KEY))
    {
        if (!piano.is_recording)
        {
            start_recording(piano);
        }
        else
        {
            stop_recording(piano);
        }
    }

    // Check for playback control
    if (key_typed(P_KEY) && !piano.is_recording)
    {
        if (!piano.is_playing)
        {
            start_playback(piano);
        }
        else
        {
            stop_playback(piano);
        }
    }

    // Check for save (only if there's a recording and not currently recording/playing)
    if (key_typed(COMMA_KEY) && !piano.is_recording && !piano.is_playing)
    {
        if (piano.recording.size() > 0)
        {
            piano.current_state = GETTING_SAVE_FILENAME;
            piano.text_input = "";
            start_reading_text(rectangle_from(160, 310, 450, 30));
        }
    }

    // Check for load
    if (key_typed(PERIOD_KEY) && !piano.is_recording && !piano.is_playing)
    {
        list_available_recordings(piano);
        piano.current_state = SHOWING_LOAD_MENU;
    }
    
    // Check if guide button was clicked
    if (is_guide_button_clicked(piano))
    {
        piano.current_state = SHOWING_GUIDE;
    }
    
    // Check if keybinds button was clicked
    if (is_keybinds_button_clicked(piano))
    {
        piano.current_state = SHOWING_KEYBINDS;
    }
}

// Handle logic for GETTING_SAVE_FILENAME state
void handle_save_state(Piano &piano)
{
    // Update text input
    piano.text_input = text_input();

    // Check if user pressed ENTER to save
    if (key_typed(RETURN_KEY))
    {
        if (piano.text_input.length() > 0)
        {
            string filename = piano.text_input + ".txt";
            save_recording_to_file(piano, filename);
            end_reading_text();
            piano.current_state = PLAYING_PIANO;
        }
    }

    // Check if user pressed ESC to cancel
    if (key_typed(ESCAPE_KEY))
    {
        end_reading_text();
        piano.current_state = PLAYING_PIANO;
    }
}

// Handle logic for SHOWING_LOAD_MENU state
void handle_load_state(Piano &piano)
{
    // Handle number key input (1-4)
    handle_load_menu_input(piano);

    // Check if user pressed ESC to cancel
    if (key_typed(ESCAPE_KEY))
    {
        piano.current_state = PLAYING_PIANO;
    }
}

// Handle logic for SHOWING_GUIDE state
void handle_guide_state(Piano &piano)
{
    // Check if guide button was clicked to close
    if (is_guide_button_clicked(piano))
    {
        piano.current_state = PLAYING_PIANO;
    }
    
    // Check if user pressed ESC to close
    if (key_typed(ESCAPE_KEY))
    {
        piano.current_state = PLAYING_PIANO;
    }
}

// Handle logic for SHOWING_KEYBINDS state
void handle_keybinds_state(Piano &piano)
{
    // Check if keybinds button was clicked to close
    if (is_keybinds_button_clicked(piano))
    {
        piano.current_state = PLAYING_PIANO;
    }
    
    // Check if user pressed ESC to close
    if (key_typed(ESCAPE_KEY))
    {
        piano.current_state = PLAYING_PIANO;
    }
}