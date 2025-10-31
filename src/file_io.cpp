#include "../include/music_header.h"
#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;
using std::string;

// Create recordings directory if it doesn't exist
void initialize_recordings_directory()
{
    try
    {
        fs::create_directories("recordings");
        write_line("INFO: 'recordings' folder ready.");
    }
    catch (const fs::filesystem_error &e)
    {
        write_line(string("WARNING: Could not create recordings folder: ") + e.what());
    }
}

// Save recording to file
void save_recording_to_file(const Piano &piano, const string &filename)
{
    string full_path = "recordings/" + filename;
    std::ofstream output_file(full_path);

    if (output_file.is_open())
    {
        for (const auto &event : piano.recording)
        {
            output_file << static_cast<int>(event.note) << " " << event.timestamp << std::endl;
        }
        output_file.close();
        write_line("Successfully saved to " + full_path);
    }
    else
    {
        write_line("Error: Could not save to " + full_path);
    }
}

// Load recording from file
void load_recording_from_file(Piano &piano, const string &filename)
{
    string full_path = "recordings/" + filename;
    std::ifstream input_file(full_path);

    if (input_file.is_open())
    {
        piano.recording.clear();
        int note_val;
        unsigned int timestamp;

        while (input_file >> note_val >> timestamp)
        {
            NoteEvent event;
            event.note = static_cast<NoteType>(note_val);
            event.timestamp = timestamp;
            piano.recording.push_back(event);
        }
        input_file.close();
        write_line("Successfully loaded from " + full_path);
    }
    else
    {
        write_line("Error: Could not load from " + full_path);
    }
}

// List available recordings from the recordings folder
void list_available_recordings(Piano &piano)
{
    piano.recording_files.clear();

    try
    {
        // Check if recordings directory exists
        if (!fs::exists("recordings") || !fs::is_directory("recordings"))
        {
            write_line("No recordings found: 'recordings' folder doesn't exist.");
            return;
        }

        // Iterate through all files in the recordings directory
        for (const auto &entry : fs::directory_iterator("recordings"))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".txt")
            {
                piano.recording_files.push_back(entry.path().filename().string());
            }
        }

        if (piano.recording_files.empty())
        {
            write_line("No .txt recordings found in 'recordings' folder.");
        }
        else
        {
            write_line("Found " + std::to_string(piano.recording_files.size()) + " recording(s):");
            for (const string &file : piano.recording_files)
            {
                write_line("  - " + file);
            }
        }
    }
    catch (const fs::filesystem_error &e)
    {
        write_line(string("Error accessing recordings folder: ") + e.what());
    }
}