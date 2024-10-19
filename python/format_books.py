import os

# Markers to define the start and end of the content
START_MARKER = "*** START"
END_MARKER = "*** END"

# Function to process each file
def process_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    # Variables to track the start and end of the relevant content
    inside_text = False
    markers_found = False
    new_lines = []

    # Iterate over the lines and extract the relevant portion
    for line in lines:
        if START_MARKER in line:
            print("Start Marker: " + line)
            inside_text = True
            markers_found = True
            continue  # Skip the line with the start marker
        elif END_MARKER in line:
            print("Endmarker: " + line)
            inside_text = False
            markers_found = True
            break  # Stop reading after the end marker

        if inside_text:
            new_lines.append(line)

    # Overwrite the file with the extracted content
    if markers_found:
        with open(file_path, 'w') as file:
            file.writelines(new_lines)

# Function to iterate through a directory and process each text file
def process_directory(directory_path):
    for filename in os.listdir(directory_path):
        if filename.endswith(".txt"):  # Only process .txt files
            file_path = os.path.join(directory_path, filename)
            print(f"Processing file: {filename}")
            process_file(file_path)

# Example usage
if __name__ == "__main__":
    directory_path = "../books"  # Replace with your directory
    process_directory(directory_path)
