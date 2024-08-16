import os
import json

NUM_TEST_CASES = 20

# test_cases = [
#     {
#         "input": [1, 2, 3, 4, 5],
#         "expected_output": "[\n    1,\n    2,\n    3,\n    4,\n    5\n]"
#     },
#     {
#         "input": [1, [2, 3], [4, [5, 6]]],
#         "expected_output": "[\n    1,\n    [\n        2,\n        3\n    ],\n    [\n        4,\n        [\n            5,\n            6\n        ]\n    ]\n]"
#     },
#     {
#         "input": [123, "Hello", True, None, False],
#         "expected_output": "[\n    123,\n    \"Hello\",\n    true,\n    null,\n    false\n]"
#     },
#     {
#         "input": {"name": "John", "age": 30, "married": False},
#         "expected_output": "{\n    \"name\": \"John\",\n    \"age\": 30,\n    \"married\": false\n}"
#     },
#     {
#         "input": {
#             "person": {
#                 "name": "Alice",
#                 "address": {
#                     "city": "Wonderland",
#                     "zipcode": "12345"
#                 }
#             }
#         },
#         "expected_output": "{\n    \"person\": {\n        \"name\": \"Alice\",\n        \"address\": {\n            \"city\": \"Wonderland\",\n            \"zipcode\": \"12345\"\n        }\n    }\n}"
#     }
# ]

if not os.path.exists("test-cases"):
    os.mkdir("test-cases")

for i in range(1, NUM_TEST_CASES + 1):
    tc_dir = f"test-cases/tc{i}"
    if (os.path.exists(tc_dir)):
        continue

    os.mkdir(tc_dir)

    with open(f"{tc_dir}/input.json", "w") as input_file:
        json.dump({}, input_file, indent=4)

    with open(f"{tc_dir}/expected_output.json", "w") as output_file:
        output_file.write("")

print("Test case directories and files created successfully.")
