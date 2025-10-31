#include "../include/music_header.h"
#include <string>
using std::string;

// Draws the entire piano on the screen
void draw_piano(Piano &piano)
{
    string title = "Seb's Piano App";
    
    // Draw white keys first
    for (int i = 0; i < piano.key_count; i++)
    {
        if (piano.keys[i].color == WHITE)
        {
            draw_piano_key(piano.keys[i]);
        }
    }

    // Draw black keys on top of white keys
    for (int i = 0; i < piano.key_count; i++)
    {
        if (piano.keys[i].color == BLACK)
        {
            draw_piano_key(piano.keys[i]);
        }
    }
    
    // Draw title
    draw_text(title, COLOR_BLACK, screen_width() / 2 - (title.length() * TEXT_FONT_SIZE) / 2, screen_height() / 4);
    
    // Draw guide button
    draw_guide_button(piano);
    
    // Draw keybinds button
    draw_keybinds_button(piano);
    
    // Draw recording/playback indicators
    if (piano.is_recording)
    {
        draw_text("RECORDING", COLOR_RED, 10, 10);
    }
    if (piano.is_playing)
    {
        draw_text("PLAYING", COLOR_GREEN, 10, 30);
    }
}

// Draws an individual piano key
void draw_piano_key(PianoKey &key)
{
    color key_color;
    color border_color = COLOR_BLACK;
    color text_color = COLOR_BLACK;
    
    // Set colors based on key state and type
    if (key.color == WHITE)
    {
        if (key.is_pressed)
        {
            key_color = COLOR_LIGHT_GRAY;
        }
        else
        {
            key_color = COLOR_WHITE;
        }
    }
    else
    {
        if (key.is_pressed)
        {
            key_color = COLOR_GRAY;
        }
        else
        {
            key_color = COLOR_BLACK;
        }
        text_color = COLOR_WHITE;
    }

    // Draw the key rectangle
    fill_rectangle(key_color, key.x, key.y, key.width, key.height);
    draw_rectangle(border_color, key.x, key.y, key.width, key.height);

    double text_x = key.x + (key.width - key.label.length() * TEXT_FONT_SIZE) / 2;
    double text_y = key.y + key.height - TEXT_FONT_SIZE - 15;
    draw_text(key.label, text_color, text_x, text_y);
}

// Draw the guide button (question mark) in top right corner
void draw_guide_button(const Piano &piano)
{
    // Draw circle background
    fill_circle(COLOR_LIGHT_BLUE, piano.guide_button_x, piano.guide_button_y, piano.guide_button_size);
    draw_circle(COLOR_BLACK, piano.guide_button_x, piano.guide_button_y, piano.guide_button_size);
    
    // Draw question mark
    draw_text("?", COLOR_BLACK, piano.guide_button_x - 3, piano.guide_button_y - 4);
    
    // Draw "Guide" text below
    draw_text("Guide", COLOR_BLACK, piano.guide_button_x - 18, piano.guide_button_y + piano.guide_button_size + 5);
}

// Draw the keybinds button in top right corner
void draw_keybinds_button(const Piano &piano)
{
    // Draw circle background - light pastel yellow
    fill_circle(rgba_color(255, 255, 200, 255), piano.keybinds_button_x, piano.keybinds_button_y, piano.keybinds_button_size);
    draw_circle(COLOR_BLACK, piano.keybinds_button_x, piano.keybinds_button_y, piano.keybinds_button_size);
    
    // Draw letter K
    draw_text("K", COLOR_BLACK, piano.keybinds_button_x - 3, piano.keybinds_button_y - 4);
    
    // Draw "Keybinds" text below
    draw_text("Keybinds", COLOR_BLACK, piano.keybinds_button_x - 28, piano.keybinds_button_y + piano.keybinds_button_size + 5);
}

// Draw the guide menu
void draw_guide_menu(const Piano &piano)
{
    // Semi-transparent overlay
    fill_rectangle(rgba_color(0, 0, 0, 150), 0, 0, screen_width(), screen_height());
    
    // Dialog box
    fill_rectangle(COLOR_WHITE, 50, 50, 700, 500);
    draw_rectangle(COLOR_BLACK, 50, 50, 700, 500);
    
    // Title
    draw_text("Piano Guide", COLOR_BLACK, 320, 70);
    
    // Keyboard mapping section
    draw_text("KEYBOARD MAPPING:", COLOR_DARK_BLUE, 70, 110);
    draw_text("White Keys: A (C), S (D), D (E), F (F), G (G), H (A), J (B)", COLOR_BLACK, 80, 135);
    draw_text("Black Keys: W (C#), E (D#), T (F#), Y (G#), U (A#)", COLOR_BLACK, 80, 155);
    
    // Major scales section
    draw_text("MAJOR SCALES:", COLOR_DARK_BLUE, 70, 190);
    draw_text("C Major: C - D - E - F - G - A - B - C", COLOR_BLACK, 80, 215);
    draw_text("G Major: G - A - B - C - D - E - F# - G", COLOR_BLACK, 80, 235);
    draw_text("F Major: F - G - A - A# - C - D - E - F", COLOR_BLACK, 80, 255);
    
    // Minor scales section
    draw_text("MINOR SCALES:", COLOR_DARK_BLUE, 70, 290);
    draw_text("A Minor: A - B - C - D - E - F - G - A", COLOR_BLACK, 80, 315);
    draw_text("E Minor: E - F# - G - A - B - C - D - E", COLOR_BLACK, 80, 335);
    draw_text("D Minor: D - E - F - G - A - A# - C - D", COLOR_BLACK, 80, 355);
    
    // Triads section
    draw_text("TRIADS:", COLOR_DARK_BLUE, 70, 390);
    draw_text("Major Triads: C (C-E-G), F (F-A-C), G (G-B-D)", COLOR_BLACK, 80, 415);
    draw_text("Minor Triads: A (A-C-E), D (D-F-A), E (E-G-B)", COLOR_BLACK, 80, 435);
    draw_text("Diminished: B (B-D-F)", COLOR_BLACK, 80, 455);
    
    // Close instruction
    draw_text("Click the question mark or press ESC to close", COLOR_DARK_GRAY, 230, 520);
}

// Draw the keybinds menu
void draw_keybinds_menu(const Piano &piano)
{
    // Semi-transparent overlay
    fill_rectangle(rgba_color(0, 0, 0, 150), 0, 0, screen_width(), screen_height());
    
    // Dialog box
    fill_rectangle(COLOR_WHITE, 100, 80, 600, 440);
    draw_rectangle(COLOR_BLACK, 100, 80, 600, 440);
    
    // Title
    draw_text("Keyboard Controls", COLOR_BLACK, 300, 100);
    
    // Piano Keys section
    draw_text("PIANO KEYS:", COLOR_DARK_BLUE, 120, 140);
    draw_text("A = C    |  W = C#", COLOR_BLACK, 130, 165);
    draw_text("S = D    |  E = D#", COLOR_BLACK, 130, 185);
    draw_text("D = E", COLOR_BLACK, 130, 205);
    draw_text("F = F    |  T = F#", COLOR_BLACK, 130, 225);
    draw_text("G = G    |  Y = G#", COLOR_BLACK, 130, 245);
    draw_text("H = A    |  U = A#", COLOR_BLACK, 130, 265);
    draw_text("J = B", COLOR_BLACK, 130, 285);
    
    // Recording and Playback section
    draw_text("RECORDING & PLAYBACK:", COLOR_DARK_BLUE, 120, 325);
    draw_text("R = Start/Stop Recording", COLOR_BLACK, 130, 350);
    draw_text("P = Play/Stop Playback", COLOR_BLACK, 130, 370);
    
    // File Operations section
    draw_text("FILE OPERATIONS:", COLOR_DARK_BLUE, 120, 410);
    draw_text(", (comma) = Save Recording", COLOR_BLACK, 130, 435);
    draw_text(". (period) = Load Recording", COLOR_BLACK, 130, 455);
    
    // Close instruction
    draw_text("Click the K button or press ESC to close", COLOR_DARK_GRAY, 240, 490);
}

// Draw the save filename input GUI
void draw_save_gui(const Piano &piano)
{
    // Semi-transparent overlay
    fill_rectangle(rgba_color(0, 0, 0, 150), 0, 0, screen_width(), screen_height());
    
    // Dialog box
    fill_rectangle(COLOR_WHITE, 150, 250, 500, 100);
    draw_rectangle(COLOR_BLACK, 150, 250, 500, 100);
    
    // Instructions
    draw_text("Enter filename (.txt will be added) and press ENTER", COLOR_BLACK, 160, 260);
    draw_text("Press ESC to cancel", COLOR_DARK_GRAY, 160, 280);
    
    // User input text
    draw_text(piano.text_input, COLOR_BLACK, 160, 310, option_to_screen());
}

// Draw the load menu GUI
void draw_load_gui(const Piano &piano)
{
    // Semi-transparent overlay
    fill_rectangle(rgba_color(0, 0, 0, 150), 0, 0, screen_width(), screen_height());
    
    // Dialog box
    fill_rectangle(COLOR_WHITE, 150, 100, 500, 400);
    draw_rectangle(COLOR_BLACK, 150, 100, 500, 400);
    
    // Instructions
    draw_text("Select a file to load (1-4) or press ESC", COLOR_BLACK, 160, 110);

    if (piano.recording_files.empty())
    {
        draw_text("No recordings found in 'recordings' folder.", COLOR_DARK_RED, 160, 150);
    }
    else
    {
        int max_files = (piano.recording_files.size() < 4) ? piano.recording_files.size() : 4;
        for (int i = 0; i < max_files; ++i)
        {
            string line = std::to_string(i + 1) + ". " + piano.recording_files[i];
            draw_text(line, COLOR_BLACK, 160, 150 + i * 30);
        }

        if (piano.recording_files.size() > 4)
        {
            draw_text("(Showing first 4 files only)", COLOR_DARK_GRAY, 160, 280);
        }
    }
}
