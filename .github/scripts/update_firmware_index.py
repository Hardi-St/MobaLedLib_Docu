import os
import json
import glob
import zipfile
import tempfile
import shutil

# Path to the folder with ZIP files (relative to repo root)
DESCRIPTIONS_DIR = "firmware"  # Search recursively
INDEX_FILE = os.path.join(DESCRIPTIONS_DIR, "index.json")

def validate_zip_contents(zip_path, desc_data):
    """
    Validate ZIP contents based on .desc JSON.
    Returns True if valid, False otherwise. Logs errors.
    """
    try:
        with zipfile.ZipFile(zip_path, 'r') as zf:
            zip_files = zf.namelist()
            
            # Always check for UF2 file: {name}-V{version}.uf2
            name = desc_data.get("name")
            version = desc_data.get("version")
            if not name or not version:
                print(f"Error: Missing 'name' or 'version' in .desc for {zip_path}")
                return False
            uf2_filename = f"{name}-V{version}.uf2"
            if uf2_filename not in zip_files:
                print(f"Error: UF2 file '{uf2_filename}' not found in {zip_path}")
                return False
            
            # Always check for .desc file: {name}-V{version}.desc
            desc_filename = f"{name}-V{version}.desc"
            if desc_filename not in zip_files:
                print(f"Error: DESC file '{desc_filename}' not found in {zip_path}")
                return False
            
            # Check for license-file if present and not empty
            license_file = desc_data.get("license-file")
            if license_file and license_file.strip():
                if license_file not in zip_files:
                    print(f"Error: License file '{license_file}' not found in {zip_path}")
                    return False
            
            return True
    except Exception as e:
        print(f"Error validating {zip_path}: {e}")
        return False

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
                                
                                # Validate ZIP contents
                                if not validate_zip_contents(zip_path, data):
                                    print(f"Skipping {zip_path} due to validation errors")
                                    continue
                                
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
        
        # Collect loose .desc files recursively (no validation for loose files)
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