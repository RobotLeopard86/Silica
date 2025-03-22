#!/usr/bin/env python3
import re
import sys
import difflib
import os
from pathlib import Path

# ANSI escape codes for colors
COLOR_RED = "\033[31m"
COLOR_GREEN = "\033[32m"
COLOR_RESET = "\033[0m"

def process_file(file_path: Path) -> bool:
    """
    Process a single file:
      - Read the content.
      - For each line, if it matches the regex, remove the directory path starting from "clang/".
      - If changes were made, show a colored unified diff and ask for confirmation.
      - If confirmed, write the new content back to the file.
    Returns True if file was modified and saved, False otherwise.
    """
    with file_path.open("r", encoding="utf-8") as f:
        old_lines = f.readlines()

    new_lines = []
    modified = False
    for line in old_lines:
        new_line = line
        if line.find("#include \"silica/") != -1:
            new_line = line.replace(".h\"", ".hpp\"")

        if new_line != line:
            modified = True
        new_lines.append(new_line)

    if not modified:
        return False

    # Generate a unified diff
    diff = list(difflib.unified_diff(old_lines, new_lines, 
                                     fromfile=str(file_path), tofile=str(file_path), lineterm=""))
    
    # Print diff with colors
    for line in diff:
        if line.startswith('---') or line.startswith('+++'):
            print(line)
        elif line.startswith('-'):
            print(f"{COLOR_RED}{line}{COLOR_RESET}")
        elif line.startswith('+'):
            print(f"{COLOR_GREEN}{line}{COLOR_RESET}")
        else:
            print(line)
    
    # Ask user for confirmation
    answer = input(f"Apply changes to {file_path}? (y/n): ").strip().lower()
    if answer == 'y':
        with file_path.open("w", encoding="utf-8") as f:
            f.writelines(new_lines)
        print(f"Changes applied to {file_path}.")
        return True
    else:
        print(f"Changes discarded for {file_path}.")
        return False

def main():
    # Use current directory or a provided directory from command-line arguments
    if len(sys.argv) > 1:
        base_dir = Path(sys.argv[1])
    else:
        base_dir = Path.cwd()

    if not base_dir.is_dir():
        print(f"Error: {base_dir} is not a directory.", file=sys.stderr)
        sys.exit(1)

    # Find all .h files (recursively)
    header_files = list(base_dir.rglob("*.hpp"))
    if not header_files:
        print("No .hpp files found.")
        return

    modified_files = 0
    for file_path in header_files:
        if process_file(file_path):
            modified_files += 1

    print(f"\nProcessed {len(header_files)} files. {modified_files} file(s) modified.")

if __name__ == '__main__':
    main()