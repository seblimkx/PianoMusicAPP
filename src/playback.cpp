#include "../include/music_header.h"

// Start playing back recorded notes
void start_playback(Piano &piano)
{
    if (piano.recording.size() > 0)
    {
        piano.is_playing = true;
        piano.is_recording = false;
        start_timer(piano.record_timer);
        piano.next_note_index = 0;
    }
}

// Stop playback
void stop_playback(Piano &piano)
{
    piano.is_playing = false;
    stop_timer(piano.record_timer);
}

// Handle playback of recorded notes
void handle_playback(Piano &piano)
{
    if (!piano.is_playing || piano.next_note_index >= piano.recording.size())
    {
        if (piano.is_playing)
            stop_playback(piano);
        return;
    }

    NoteEvent next_event = piano.recording[piano.next_note_index];
    if (timer_ticks(piano.record_timer) >= next_event.timestamp)
    {
        // Find and play the corresponding key
        for (int i = 0; i < piano.key_count; ++i)
        {
            if (piano.keys[i].note == next_event.note)
            {
                play_note_sound(piano.keys[i]);
                break;
            }
        }
        piano.next_note_index++;
    }
}