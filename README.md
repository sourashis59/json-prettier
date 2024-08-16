# json-prettier
- A C++ program, that can format an unformatted json string.
- Build the project using `make` and use the program `json_formatter.out`.
- Pass the input and output file path as command line arguments, and the input json will be formatted and stored in output file.
- 
    ```bash
    ./json_formatter.out input.json output.json 
    ```
- Example:
    - Input json:
        ```JSON
        {"widget": {"debug": "on","window":{"title": "Sample Konfabulator Widget", "name": "main_window", "width": 500, "height": 500
        },
                                                    "image": { 
                                        "src": "Images/Sun.png",
                                "name": "sun1",
                        "hOffset": null,
                "vOffset": null,
        "alignment": "center","flag":true
                                                                            },
                                                                    "text": {
                                                                                    "data": "Click Here",
                                                                                                        "size": 36,
                                                                                                        "style": "bold",
                                            "name": "text1",
                                    "hOffset": 250,"vOffset": 100,                      "alignment": "center",
            "onMouseUp": "sun1.opacity = (sun1.opacity / 100) * 90;"}}
                        }            ```
    - Formatted output:
        ```JSON
        {
            "widget": {
                "debug": "on",
                "window": {
                    "title": "Sample Konfabulator Widget",
                    "name": "main_window",
                    "width": 500,
                    "height": 500
                },
                "image": {
                    "src": "Images/Sun.png",
                    "name": "sun1",
                    "hOffset": null,
                    "vOffset": null,
                    "alignment": "center",
                    "flag": true
                },
                "text": {
                    "data": "Click Here",
                    "size": 36,
                    "style": "bold",
                    "name": "text1",
                    "hOffset": 250,
                    "vOffset": 100,
                    "alignment": "center",
                    "onMouseUp": "sun1.opacity = (sun1.opacity / 100) * 90;"
                }
            }
        }        
        ```

## Working:
- First this program parses the input string and builds the parse tree.
- Then proper amount of indentation is applied on each node.