import kagglehub
import shutil
import os

def download_dataset(destination="data/creditcard.csv"):
    path = kagglehub.dataset_download("mlg-ulb/creditcardfraud")
    print("Downloaded to:", path)  # NEW: print path location

    # Let's see what's inside the downloaded folder
    print("Files in downloaded folder:", os.listdir(path))

    source_file = os.path.join(path, "creditcard.csv")

    # Double-check if the source file exists
    if not os.path.exists(source_file):
        print("creditcard.csv not found in path:", source_file)
        return

    os.makedirs("data", exist_ok=True)
    shutil.copy(source_file, destination)
    print("Dataset copied to:", destination)

if __name__ == "__main__":
    download_dataset()
