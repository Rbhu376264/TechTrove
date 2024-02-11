#!/bin/bash

# Actual path to the "Introduction to Artificial Intelligence" folder in your TechTrove repository
basePath="/Users/rbhu_gandhiog/TheDevDiary/TechTrove/Introduction to Artificial Intelligence"

# URLs array extracted from the file
urls=(
  "https://github.com/CSCI-360/lab1-Rbhu376264.git"
  "https://github.com/CSCI-360/lab2-Rbhu376264.git"
  "https://github.com/CSCI-360/lab3-Rbhu376264.git"
  "https://github.com/CSCI-360/lab4-Rbhu376264.git"
  "https://github.com/CSCI-360/lab5-Rbhu376264.git"
)

# Loop through the URLs and create a folder for each lab, then clone the content
for url in "${urls[@]}"; do
  # Extract the lab name from the URL (e.g., lab1, lab2, etc.)
  labName=$(echo $url | grep -o "lab[0-9]\+")
  
  # Define the full path for the lab folder
  labPath="$basePath/$labName"

  # Create a directory for the lab inside the "Introduction to Artificial Intelligence" folder
  mkdir -p "$labPath"
  
  # Clone the repository into the created directory
  git clone "$url" "$labPath"
  
  echo "Cloned $url into $labPath"
done

echo "All lab folders have been created and repositories cloned."
