# CS4437DSA
Search engine for text books, focusing in on the data structure for storing files and algorithms for search, insertion and deletion.

## Prerequisites
### Download Books
1. Download Books from [https://www.gutenberg.org/browse/scores/top](https://www.gutenberg.org/browse/scores/top) using python script
2. Format the books using python script //removes unwanted text form start and end of the book
 ```sh
  cd python
  python3 pull_books.py
  python3 format_books.py
  cd ..
```

## Build Instructions

### For Windows
1. Make sure you have CMake installed</br>
*you can check this by running* `cmake --version`
2. Open command prompt and run the following commands in the project directory
```sh
mkdir build
cd build
cmake ..
cmake --build .
```

### For Mac/Linux
1. Make sure you have CMake installed</br>
*you can check this by running* `cmake --version`
2. Open a terminal and run the following command in the project directory
```sh
./rebuld
```
## Running the application
1. Open a terminal/command prompt and change directory into the `build` directory
2. Run the following command to run the application:
```sh
cd build
./App
```
### Running tests
1. Open a terminal/command prompt and change directory into the `build` directory
2. Run the following command to run the application:
```sh
ctest
```

## Example Usage
- Once the application is running, you can use the following commands to interact with the application:
    - `1` -  reload index books, if a new book is added this will update the index
    - `2 `: search books for key word
    - `3 <word>`: search books for a specific word
    - `4`: exit the application


   // Example Terminal Output
   ``` sh
   1
   ```


