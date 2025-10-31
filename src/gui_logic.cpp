#include "../include/music_header.h"

// Calculate and set all GUI positions for the piano
void layout_piano(Piano &piano)
{
    piano.total_width = 7 * WHITE_KEY_WIDTH;
    piano.total_height = WHITE_KEY_HEIGHT;
    piano.x = (screen_width() - piano.total_width) / 2;
    piano.y = (screen_height() - piano.total_height) / 2;

    // Layout white keys
    int white_key_index = 0;
    for (int i = 0; i < piano.key_count; i++)
    {
        if (piano.keys[i].color == WHITE)
        {
            piano.keys[i].width = WHITE_KEY_WIDTH;
            piano.keys[i].height = WHITE_KEY_HEIGHT;
            piano.keys[i].x = piano.x + white_key_index * WHITE_KEY_WIDTH;
            piano.keys[i].y = piano.y;
            white_key_index++;
        }
    }

    // Layout black keys
    int black_key_positions[] = {1, 2, 4, 5, 6}; // Positions after which white keys
    int black_key_index = 0;
    for (int i = 0; i < piano.key_count; i++)
    {
        if (piano.keys[i].color == BLACK)
        {
            piano.keys[i].width = BLACK_KEY_WIDTH;
            piano.keys[i].height = BLACK_KEY_HEIGHT;
            piano.keys[i].x = piano.x + black_key_positions[black_key_index] * WHITE_KEY_WIDTH - (BLACK_KEY_WIDTH / 2);
            piano.keys[i].y = piano.y;
            black_key_index++;
        }
    }
    
    // Layout guide button in top right corner
    piano.guide_button_size = 20.0;
    piano.guide_button_x = screen_width() - 40;
    piano.guide_button_y = 30;
    
    // Layout keybinds button below guide button
    piano.keybinds_button_size = 20.0;
    piano.keybinds_button_x = screen_width() - 40;
    piano.keybinds_button_y = 95;
}

// Handle input for the load menu
void handle_load_menu_input(Piano &piano)
{
    const key_code key_map[] = {NUM_1_KEY, NUM_2_KEY, NUM_3_KEY, NUM_4_KEY};

    for (int i = 0; i < 4 && i < piano.recording_files.size(); ++i)
    {
        if (key_typed(key_map[i]))
        {
            load_recording_from_file(piano, piano.recording_files[i]);
            piano.current_state = PLAYING_PIANO;
            return;
        }
    }
}

// Check if guide button was clicked
bool is_guide_button_clicked(const Piano &piano)
{
    if (mouse_clicked(LEFT_BUTTON))
    {
        point_2d mouse_pos = mouse_position();
        double dx = mouse_pos.x - piano.guide_button_x;
        double dy = mouse_pos.y - piano.guide_button_y;
        double distance = sqrt(dx * dx + dy * dy);
        
        return distance <= piano.guide_button_size;
    }
    return false;
}

// Check if keybinds button was clicked
bool is_keybinds_button_clicked(const Piano &piano)
{
    if (mouse_clicked(LEFT_BUTTON))
    {
        point_2d mouse_pos = mouse_position();
        double dx = mouse_pos.x - piano.keybinds_button_x;
        double dy = mouse_pos.y - piano.keybinds_button_y;
        double distance = sqrt(dx * dx + dy * dy);
        
        return distance <= piano.keybinds_button_size;
    }
    return false;
}