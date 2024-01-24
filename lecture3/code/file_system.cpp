#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

void file_system_equivalent()
{
    // Construct a path for the local directory
    std::filesystem::path local(".");
    std::cout << "local == " << local << "\n";    // local == "."

    // Get the absolute path, i.e. a path from root
    std::filesystem::path from_root = absolute(local);
    std::cout << "from_root == " << from_root
              << "\n";    // from_root == "/some/path/."

    // Get the canonical (normalized) full path
    std::filesystem::path unique = canonical(local);
    std::cout << "unique == " << from_root << "\n";    // unique == "/some/path"

    bool eq1 = std::filesystem::equivalent(local, from_root);
    bool eq2 = std::filesystem::equivalent(local, unique);
    std::cout << std::boolalpha << "eq1 == " << eq1 << ", eq2 == " << eq2
              << "\n";    // eq1 == true, eq2 == true
}

// process each std::filesystem::directory_entry
void print_file_size(std::filesystem::directory_entry const& entry)
{
    if (entry.is_regular_file())    // Type of object
    {
        // Filename can be extracted from the path
        auto filename = entry.path().filename();
        std::cout << filename << ": " << file_size(entry)
                  << "\n";    // size, permissions, etc...
    }
}

void enumerate_files()
{
    std::filesystem::path local(".");

    // iterate over entries in directory specified by path
    for (auto const& entry : std::filesystem::directory_iterator(local))
    {
        print_file_size(entry);
    }

    // recursively iterate over entries in directory specified by path
    for (auto const& entry :
        std::filesystem::recursive_directory_iterator(local))
    {
        print_file_size(entry);
    }
}

void create_backup()
{
    // Create a file with the content: "Current content\n"
    std::filesystem::path file = "current_file";
    {
        // canonical path must exists, however, since we are just
        // about to create the file, we need to use weakly_canonical
        std::ofstream f(weakly_canonical(file));
        f << "Current content\n";
    }

    // Create a directory if it doesn't exist
    std::filesystem::path backup_folder = "./backup";
    if (!exists(backup_folder))
        create_directory(backup_folder);

    // Check for sufficient space
    if (space(backup_folder).available < file_size(file))
        throw std::runtime_error("Not enough space for backup.");

    // Create a "unique" filename in the backup folder
    std::filesystem::path backup_file = backup_folder / file.filename();

    // Copy the file to backup
    copy(file, backup_file);

    // Update the symlink to point to this backup
    std::filesystem::path symlink = file.parent_path() / "current_backup";
    if (exists(symlink))
        remove(symlink);
    create_symlink(backup_file, symlink);
}

int main()
{
    file_system_equivalent();
    enumerate_files();
    create_backup();
}
