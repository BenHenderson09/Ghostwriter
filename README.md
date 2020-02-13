# Ghostwriter
Ghostwriter is a CLI tool that's used to paraphrase text, allowing users to quickly put extracts in "their own words".
When users provided input text to Ghostwriter, the words will be analysed and syonyms will be determined in order to act
as a replacement for the original word.

## Program Details
 - Made with C++
 - Built with CMake
 - Uses [WordsAPI](https://www.wordsapi.com/) to find synonyms
 - Uses [nlohmann/json](https://github.com/nlohmann/json) for configurations and API responses
 - Uses [libcurl](https://curl.haxx.se/libcurl/) to carry out HTTP requests to API
 
 ## Installation
 Installation is fairly simple, following the standard method of installing with CMake.
 1. `git clone https://github.com/BenHenderson09/Ghostwriter`
 2. `mkdir -p Ghostwriter/build && cd build`
 3. `cmake .. && make install`
 
 **Note:** As of yet, an API key for the [WordsAPI](https://www.wordsapi.com/) must be inserted
 [here](https://github.com/BenHenderson09/Ghostwriter/blob/master/src/config/WordApiConfig.hpp#L10).
 
 ## Flags
| Flag                     | Type          | Description                                           |
|--------------------------|---------------| ------------------------------------------------------|
| `--input-text`           | string        | Enter input text as a string in the terminal.         |
| `--input-file`           | string        | Path of text file to be read.                         |
| `--output-file`          | string        | Path of output file to be written to (will overwrite).|
| `--mulitple-suggestions` | boolean       | Provides multiple paraphrasing options for each word. |

Either `--input-text` or `--input-file` **must** be specified, but not both. All other flags are optional.

 ## Example
 Command: `ghostwriter --input-text hello there --multiple-suggestions`
 
 Output: `(hi/how-do-you-do/howdy/hullo/hello) (thither/there)`