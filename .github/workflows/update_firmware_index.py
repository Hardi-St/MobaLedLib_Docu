import os
import json
import glob
import zipfile
import tempfile
import shutil

# Path to the folder with ZIP files (relative to repo root)
DESCRIPTIONS_DIR = "firmware"  # Search recursively
INDEX_FILE = os.path.join(DESCRIPTIONS_DIR, "index.json")

def update_index():
    index = []
    temp_dir = tempfile.mkdtemp()  # Temporary directory for extraction
    
    try:
        # Collect all .zip files recursively
        zip_files = glob.glob(os.path.join(DESCRIPTIONS_DIR, "**/*.zip"), recursive=True)
        
        for zip_path in zip_files:
            try:
                with zipfile.ZipFile(zip_path, 'r') as zf:
                    # Find .desc files in the ZIP
                    desc_members = [m for m in zf.namelist() if m.endswith('.desc')]
                    for member in desc_members:
                        # Extract temporarily
                        extracted_path = zf.extract(member, temp_dir)
                        try:
                            with open(extracted_path, 'r', encoding='utf-8') as f:
                                data = json.load(f)
                                # Add metadata (relative path to ZIP)
                                data["zip_path"] = os.path.relpath(zip_path, DESCRIPTIONS_DIR)  # e.g. "subfolder/MyFile.zip"
                                data["desc_filename"] = member
                                index.append(data)
                        except json.JSONDecodeError as e:
                            print(f"Error parsing {member} in {zip_path}: {e}")
                        except Exception as e:
                            print(f"Error reading {member} in {zip_path}: {e}")
            except zipfile.BadZipFile as e:
                print(f"Error opening {zip_path}: {e}")
            except Exception as e:
                print(f"Error with {zip_path}: {e}")
        
        # Collect loose .desc files recursively
        loose_desc_files = glob.glob(os.path.join(DESCRIPTIONS_DIR, "**/*.desc"), recursive=True)
        for file_path in loose_desc_files:
            try:
                with open(file_path, 'r', encoding='utf-8') as f:
                    data = json.load(f)
                    data["zip_path"] = None  # Mark as loose file
                    data["desc_path"] = os.path.relpath(file_path, DESCRIPTIONS_DIR)  # e.g. "subfolder/Pico2x3-Tiny.desc"
                    index.append(data)
            except json.JSONDecodeError as e:
                print(f"Error parsing {file_path}: {e}")
            except Exception as e:
                print(f"Error reading {file_path}: {e}")
    
    finally:
        # Clean up temporary directory
        shutil.rmtree(temp_dir, ignore_errors=True)
    
    # Write the index as JSON array
    with open(INDEX_FILE, 'w', encoding='utf-8') as f:
        json.dump(index, f, indent=2, ensure_ascii=False)
    
    print(f"Index updated: {len(index)} entries in {INDEX_FILE}")

if __name__ == "__main__":
    update_index()