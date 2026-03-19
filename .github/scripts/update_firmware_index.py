# ... (bestehender Code)

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
                print(f"::warning::Missing 'name' or 'version' in .desc for {zip_path}")
                return False
            uf2_filename = f"{name}-V{version}.uf2"
            if uf2_filename not in zip_files:
                print(f"::warning::UF2 file '{uf2_filename}' not found in {zip_path}")
                return False
            
            # Always check for .desc file: {name}-V{version}.desc
            desc_filename = f"{name}-V{version}.desc"
            if desc_filename not in zip_files:
                print(f"::warning::DESC file '{desc_filename}' not found in {zip_path}")
                return False
            
            # Check for license-file if present and not empty
            license_file = desc_data.get("license-file")
            if license_file and license_file.strip():
                if license_file not in zip_files:
                    print(f"::warning::License file '{license_file}' not found in {zip_path}")
                    return False
            
            return True
    except Exception as e:
        print(f"::error::Error validating {zip_path}: {e}")
        return False

def update_index():
    # ... (bestehender Code)
    
    for zip_path in zip_files:
        # ... (bestehender Code)
        except json.JSONDecodeError as e:
            print(f"::warning::Error parsing {member} in {zip_path}: {e}")
        except Exception as e:
            print(f"::error::Error reading {member} in {zip_path}: {e}")
        # ... (weitere except-Blöcke)
        except zipfile.BadZipFile as e:
            print(f"::warning::Error opening {zip_path}: {e}")
        except Exception as e:
            print(f"::error::Error with {zip_path}: {e}")
    
    # ... (für loose .desc files)
    except json.JSONDecodeError as e:
        print(f"::warning::Error parsing {file_path}: {e}")
    except Exception as e:
        print(f"::error::Error reading {file_path}: {e}")
    
    # ... (restlicher Code)