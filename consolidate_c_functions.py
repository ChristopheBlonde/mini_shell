import os
import re

def get_functions_from_file(filepath):
    with open(filepath, 'r') as file:
        code = file.read()
    
    # Regular expression to match C function definitions
    function_pattern = re.compile(r'\b(?:[a-zA-Z_][a-zA-Z0-9_]*\s+)+[a-zA-Z_][a-zA-Z0-9_]*\s*\([^)]*\)\s*{[^}]*}')
    functions = function_pattern.findall(code)
    return functions

def write_functions_to_file(functions, output_file):
    with open(output_file, 'w') as file:
        for func in functions:
            file.write(func)
            file.write('\n\n')

def main(input_directory, output_file):
    all_functions = []
    for root, _, files in os.walk(input_directory):
        for file in files:
            if file.endswith('.c'):
                filepath = os.path.join(root, file)
                functions = get_functions_from_file(filepath)
                all_functions.extend(functions)
    write_functions_to_file(all_functions, output_file)

if __name__ == '__main__':
    input_directory = './src'  # Change this to your directory
    output_file = './all_functions.c'
    main(input_directory, output_file)
