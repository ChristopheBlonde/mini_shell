import os

def split_file(input_file):
    # Créer un dossier pour stocker les sous-dossiers et fichiers
    output_folder = "split_files"
    os.makedirs(output_folder, exist_ok=True)

    with open(input_file, 'r') as file:
        content = file.read()
    
    chunk_size = 4095
    num_chunks = (len(content) + chunk_size - 1) // chunk_size
    
    for i in range(num_chunks):
        start = i * chunk_size
        end = (i + 1) * chunk_size
        chunk_content = content[start:end]

        # Créer un sous-dossier pour chaque chunk
        folder_name = os.path.join(output_folder, f"chunk_{i}")
        os.makedirs(folder_name, exist_ok=True)

        # Écrire le contenu du chunk dans un fichier
        with open(os.path.join(folder_name, f"{input_file}_{i}.txt"), 'w') as chunk_file:
            chunk_file.write(chunk_content)

    print(f"Le fichier {input_file} a été divisé en {num_chunks} chunks dans le dossier {output_folder}.")

if __name__ == "__main__":
    input_file = input(all_functions.c)
    split_file(input_file)
